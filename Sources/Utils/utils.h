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

#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QApplication>

#include "legal.h"
#include "appinfos.h"

namespace Utils
{
    QString getUserName();
    QString getPasswordAsMask(QString password, QString mask);
    QString legalText();
    QString legalTextHTML();
    QString infosText();
    QString welcomeHTML();
    QString appVersion();
}

#endif // UTILS_H
