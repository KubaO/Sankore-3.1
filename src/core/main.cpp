/*
 * Copyright (C) 2010-2013 Groupement d'Intérêt Public pour l'Education Numérique en Afrique (GIP ENA)
 *
 * This file is part of Open-Sankoré.
 *
 * Open-Sankoré is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * Open-Sankoré is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Sankoré.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <QtWidgets>

#include "frameworks/UBPlatformUtils.h"
#include "frameworks/UBFileSystemUtils.h"

#include "UBApplication.h"
#include "UBSettings.h"

/* Uncomment this for memory leaks detection */
/*
#if defined(WIN32) && defined(_DEBUG)
     #define _CRTDBG_MAP_ALLOC
     #include <stdlib.h>
     #include <crtdbg.h>
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
#endif
*/

static QtMessageHandler previousHandler;

void ub_message_output(QtMsgType type, const QMessageLogContext &context, const QString & msg) {
#if defined(QT_NO_DEBUG)
    // Suppress qDebug output in release builds
    if (type != QtDebugMsg)
    {
        previousHandler(type, context, msg);
    }

#else
    // Default output in debug builds
    previousHandler(type, context, msg);
#endif

    /// TODO Don't reopen the log all the time.
    if (UBApplication::app() && UBApplication::app()->isVerbose()) {
        QString logFileNamePath = UBSettings::userDataDirectory() + "/log/uniboard.log";
        QFile logFile(logFileNamePath);

        if (logFile.exists() && logFile.size() > 10000000)
            logFile.remove();

        if (logFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&logFile);
            out << QDateTime::currentDateTime().toString(Qt::ISODate)
                << "      " << context.file << ":" << context.line << msg << "\n";
        }
    }
}

int main(int argc, char *argv[]) 
{

    // Uncomment next section to have memory leaks information
    // tracing in VC++ debug mode under Windows
/*
#if defined(_MSC_VER) && defined(_DEBUG)
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
*/

    Q_INIT_RESOURCE(sankore);

    previousHandler = qInstallMessageHandler(ub_message_output);

    UBApplication app("Sankore", argc, argv);

    /** TODO Revisit the codecs.
     * We need to ensure that the codecs used for file paths are consistent with the
     * platform. QFile is doing the right thing, but there might be excursions through
     * const char * that would have the local 8 bit encoding.
     * The source code itself is UTF-8.
     */

    QStringList args = app.arguments();

    QString dumpPath = UBSettings::userDataDirectory() + "/log";
    QDir logDir(dumpPath);
    if (!logDir.exists())
        logDir.mkdir(dumpPath);

    QString fileToOpen;

      if (args.size() > 1) {
        // On Windows/Linux first argument is the file that has been double clicked.
        // On Mac OSX we use FileOpen QEvent to manage opening file in current instance. So we will never
        // have file to open as a parameter on OSX.

        QFile f(args[1]);

        if (f.exists()) {
            fileToOpen += args[1];
        }
    }

    //Hotfix. We allways have the single instance application independent from number of parameters
    if (app.sendMessage(UBSettings::appPingMessage, 20000)) {
        if (!fileToOpen.isNull()) {
            app.sendMessage(fileToOpen, 1000000);
        }
        return 0;
    }

    app.initialize(false);

    QObject::connect(&app, SIGNAL(messageReceived(const QString&)), &app, SLOT(handleOpenMessage(const QString&)));

    qDebug() << "file name argument" << fileToOpen;
    int result = app.exec(fileToOpen);

    app.cleanup();

    qDebug() << "application is quitting";



    return result;

}
