/************************ LICENSING & COPYRIGHT ***********************
Copyright © 2017-2018 Grégoire BOST

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

#ifndef MAINUTILS_H
#define MAINUTILS_H

#include <QApplication>

#include <QTranslator>

#include <QDebug>

#include "../Core/Core/core.h"
#include "../Core/SettingsManager/settingsmanager.h"
#include "../Core/UniqueProcessChecker/uniqueprocesschecker.h"

namespace MainUtils {
    void translate(QApplication *a, const QString &lang);
    bool setAsUniqueProcess(QApplication &a);
}

#endif // MAINUTILS_H
