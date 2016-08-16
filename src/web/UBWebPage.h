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



#ifndef UBWEBPAGE_H_
#define UBWEBPAGE_H_

/*
 * Use UBWebEnginePage instead of QWebEnginePage to log JavaScript console messages with qDebug
 */

#include <QWebEnginePage>

class UBWebEnginePage : public QWebEnginePage
{
    Q_OBJECT;

    public:
        UBWebEnginePage(QObject *parent = 0);
        virtual ~UBWebEnginePage();

        void javaScriptConsoleMessage(QWebEnginePage::JavaScriptConsoleMessageLevel level,
                                      const QString &message, int lineNumber, const QString &sourceID) override;
    private:
        QString mCachedUserAgentString;
};

#endif /* UBWEBPAGE_H_ */
