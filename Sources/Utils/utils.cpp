/************************ LICENSING & COPYRIGHT ***********************
Copyright © 2017 Grégoire BOST

This file is part of MiniClipBoard.

MiniClipBoard is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MiniClipBoard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with MiniClipBoard.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include "utils.h"

QString Utils::getPasswordAsMask(QString password, QString mask)
{
    QString str;

    for(int i(0) ; i < password.length() ; i++)
    {
        str += mask;
    }

    return str;
}

QString Utils::legalText()
{
    return QString(LEGAL_TEXT);
}

QString Utils::legalTextHTML()
{
    return QString(LEGAL_TEXT_HTML);
}

QString Utils::infosText()
{
    QString text = QObject::tr("<style>" \
                               "a{color: #3399ff;}" \
                               "</style>" \
                               "<p>" \
                               "<h1>MiniClipBoard</h1>" \
                               "This application is made in C++, based on <a href=\"www.qt.io\">Qt</a> %1.<br>" \
                               "For more informations, please visit the <a href=\"https://github.com/GregPlusPlus/MiniClipBoard\">official website</a>." \
                               "<hr>" \
                               "Copyright © 2017 Grégoire BOST<br><br>" \
                               "%2" \
                               "</p>").arg(QT_VERSION_STR).arg(legalTextHTML());

    return text;
}

QString Utils::welcomeHTML()
{
    QFile file(":/html/welcome");
    file.open(QFile::ReadOnly);

    QString html = file.readAll();

    file.close();

    return html.toUtf8();
}

QString Utils::appVersion()
{
    return QString(APP_VERSION);
}

QString Utils::getUserName()
{
    QString name = qgetenv("USER");

    if(name.isEmpty()) {
        name = qgetenv("USERNAME");
    }

    return name.toUtf8();
}
