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

#include "hotkeysmanager.h"

HotKeysManager::HotKeysManager(QObject *parent) : QObject(parent)
{
    init();
}

void HotKeysManager::init()
{
    m_hotkeyManager = new UGlobalHotkeys(nullptr);

    connect(m_hotkeyManager, &UGlobalHotkeys::activated, [=](size_t id) {
        switch (id) {
        case Action_ToggleWindow:
            emit toggleWindow();
            break;
        case Action_Close:
            emit close();
            break;
        case Action_PauseResume:
            emit pauseResume();
            break;
        case Action_ClearClipboard:
            emit clearCliboard();
            break;
        default:
            emit unknownHotKeyActivated(id);
            break;
        }
    });
}

void HotKeysManager::registerHotKey(const HotKeysAction &action, const QString sequence)
{
    //m_hotkeyManager->unregisterHotkey((size_t)action);

    m_sequences[action] = sequence;

    m_hotkeyManager->registerHotkey(sequence, size_t(action));
}

void HotKeysManager::registerHotKeys(const QMap<size_t, QString> sequences)
{
    m_hotkeyManager->unregisterAllHotkeys();
    m_sequences.clear();

    for(size_t action : sequences.keys()) {
        registerHotKey(static_cast<HotKeysManager::HotKeysAction>(action), sequences.value(action));
    }
}

void HotKeysManager::unregisterAll()
{
    m_hotkeyManager->unregisterAllHotkeys();
}

QMap<size_t, QString> HotKeysManager::sequences() const
{
    return m_sequences;
}
