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

#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>

#include <QMenu>
#include <QAction>

class Tray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit Tray(QWidget *parent = nullptr);

    bool paused() const;

    bool anchored() const;

signals:
    void quit();
    void pauseToggled(bool paused);
    void clear();
    void clearClipboard();
    void moreOptions();
    void triggered();
    void resetSize();
    void toggledAnchor(bool anchored);
    void help();

public slots:
    void trayActivated(QSystemTrayIcon::ActivationReason reason);
    void pause();
    void toggleAnchor();

private:
    QMenu   *mw_menu;
    QAction *m_pauseAction;
    QAction *m_clearAction;
    QAction *m_clearClipboardAction;
    QAction *m_moreOptionsAction;
    QAction *m_anchorAction;
    QAction *m_resetSizeAction;
    QAction *m_helpAction;
    QAction *m_quitAction;

    bool m_paused = false;
    bool m_anchored = true;
};

#endif // TRAY_H
