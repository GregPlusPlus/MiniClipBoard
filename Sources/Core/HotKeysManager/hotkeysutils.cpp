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

#include "hotkeysutils.h"

QMap<size_t, QString> HotKeysUtils::loadSequences(const QString &fileName)
{
    QFile file(fileName);

    QMap<size_t, QString> sequences;

    if(file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_9);

        stream >> sequences;
    }

    return sequences;
}

void HotKeysUtils::saveSequences(const QMap<size_t, QString> &sequences, const QString &fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_9);

        stream << sequences;
    }
}

void HotKeysUtils::fillDefaultSequences(HotKeysManager *manager)
{
    manager->registerHotKey(HotKeysManager::Action_ToggleWindow,    "Ctrl+Alt+F1");
    manager->registerHotKey(HotKeysManager::Action_Close,           "Ctrl+Alt+F4");
    manager->registerHotKey(HotKeysManager::Action_PauseResume,     "Ctrl+Alt+F2");
    manager->registerHotKey(HotKeysManager::Action_ClearClipboard,  "Ctrl+Alt+F3");
}

QString HotKeysUtils::fileName()
{
    return Utils::appDataPath() + "hotkeys";
}
