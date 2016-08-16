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



#include "UBWebPage.h"

#include <QtCore>

#include "pdf/UBWebPluginPDFWidget.h"

#include "core/memcheck.h"


/// TODO Inject support for PDF into the browser
#if 0
class UBWebPluginFactory : public QWebPluginFactory
{
    public:

    UBWebPluginFactory(QObject *parent = 0) : QWebPluginFactory(parent)
    {
        // NOOP
    }

    QList<Plugin> plugins() const
    {
        QStringList pdfExtensions;
        pdfExtensions << "pdf";
        MimeType pdfMimeType = {"application/x-ub-pdf", "Portable Document Format", pdfExtensions};
        QList<MimeType> mimeTypes;
        mimeTypes << pdfMimeType;
        Plugin pdfPlugin = {"PDF Plugin", "Display PDF files", mimeTypes};
        QList<Plugin> plugins;
        plugins << pdfPlugin;
        return plugins;
    }

    QObject* create(const QString &mimeType, const QUrl &url, const QStringList &argumentNames, const QStringList &argumentValues) const
    {
        Q_UNUSED(url);
        Q_UNUSED(argumentNames);
        Q_UNUSED(argumentValues);

        if (mimeType == "application/x-ub-pdf")
        {
            UBWebPluginPDFWidget *pdfWidget = new UBWebPluginPDFWidget(url);
            pdfWidget->setObjectName("PDFWebPluginWidget");
            return pdfWidget;
        }
        return 0;
    }
};
#endif


UBWebEnginePage::UBWebEnginePage(QObject *parent)
    : QWebPage(parent)
{
#if 0
    mPluginFactory = new UBWebPluginFactory();
    setPluginFactory(mPluginFactory);
#endif
}

UBWebEnginePage::~UBWebEnginePage()
{
}


void UBWebEnginePage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
    Q_UNUSED(level);
    qDebug("JavaScript> %s (%s:%d)", qPrintable(message), qPrintable(sourceID), lineNumber);
}

