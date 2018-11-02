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

#ifndef HOTKEYSMANAGER_H
#define HOTKEYSMANAGER_H

#include <QObject>
#include <QMap>

#include <QDebug>

#include "../../Libs/UGlobalHotkey/uglobal.h"
#include "../../Libs/UGlobalHotkey/uglobalhotkeys.h"

class HotKeysManager : public QObject
{
    Q_OBJECT

public:
    enum HotKeysAction {
        Action_Unknown,
        Action_ToggleWindow,
        Action_Close,
        Action_PauseResume,
        Action_ClearClipboard
    };

public:
    explicit HotKeysManager(QObject *parent = nullptr);

    QMap<size_t, QString> sequences() const;

signals:
    void unknownHotKeyActivated(size_t id);

    void toggleWindow();
    void close();
    void pauseResume();
    void clearCliboard();

public slots:
    void registerHotKey(const HotKeysAction &action, const QString sequence);
    void registerHotKeys(const QMap<size_t, QString> sequences);
    void unregisterAll();

private:
    UGlobalHotkeys *m_hotkeyManager;

    QMap<size_t, QString> m_sequences;

private:
    void init();
};

#endif // HOTKEYSMANAGER_H
