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

#include "tray.h"

Tray::Tray(QWidget *parent) : QSystemTrayIcon(parent)
{
    setIcon(QIcon(QPixmap(20, 20))); // Default icon

    m_paused = false;

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
    mw_menu = new QMenu(parent);

    m_pauseAction = mw_menu->addAction(QIcon(":/icons/ic_pause_circle_outline_white_18dp"), tr("&Pause"), this, SLOT(pause()));
    m_clearClipboardAction = mw_menu->addAction(QIcon(":/icons/ic_remove_circle_outline_white_18dp"), tr("&Clear clipboard"), this, SIGNAL(clearClipboard()));
    m_clearAction = mw_menu->addAction(QIcon(":/icons/ic_clear_white_18dp"), tr("&Clear"), this, SIGNAL(clear()));
    mw_menu->addSeparator();
    m_resetSizeAction = mw_menu->addAction(QIcon(":/icons/ic_crop_free_white_18dp"), tr("&Reset size"), this, SIGNAL(resetSize()));
    mw_menu->addSeparator();
    m_helpAction = mw_menu->addAction(QIcon(":/icons/ic_help_outline_white_18dp"), tr("&Help/Settings"), this, SIGNAL(help()));
    m_quitAction = mw_menu->addAction(QIcon(":/icons/ic_exit_to_app_white_18dp"), tr("&Quit"), this, SIGNAL(quit()));

    setContextMenu(mw_menu);
}

void Tray::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        emit triggered();
        break;
    default:
        break;
    }
}

void Tray::pause()
{
    m_paused = !m_paused;

    if(m_paused) {
        m_pauseAction->setIcon(QIcon(":/icons/ic_pause_circle_filled_white_18dp"));
    } else {
        m_pauseAction->setIcon(QIcon(":/icons/ic_pause_circle_outline_white_18dp"));
    }

    emit pauseToggled(m_paused);
}

bool Tray::paused() const
{
    return m_paused;
}
