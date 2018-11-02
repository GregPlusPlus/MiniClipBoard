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

#include "tray.h"

Tray::Tray(QWidget *parent) : QSystemTrayIcon(parent)
{
    QPixmap nonePix(20, 20);
    nonePix.fill(QColor(0, 0, 0, 0));

    setIcon(QIcon(nonePix)); // Default icon

    connect(this, &Tray::activated, this, &Tray::trayActivated);
    mw_menu = new QMenu(parent);

    m_pauseAction           = mw_menu->addAction(QIcon(":/icons/ic_pause_circle_outline_white_18dp"), tr("&Pause"),             this, &Tray::pause);
    m_clearClipboardAction  = mw_menu->addAction(QIcon(":/icons/ic_remove_circle_outline_white_18dp"), tr("&Clear clipboard"),  this, &Tray::clearClipboard);
    m_clearAction           = mw_menu->addAction(QIcon(":/icons/ic_clear_white_18dp"), tr("&Clear"),                            this, &Tray::clear);
    m_moreOptionsAction     = mw_menu->addAction(QIcon(":/icons/ic_more_horiz_white_18dp"), tr("&More options"),                this, &Tray::moreOptions);
    mw_menu->addSeparator();
    m_resetSizeAction       = mw_menu->addAction(QIcon(":/icons/ic_fullscreen_exit_white_18dp"), tr("&Reset size"),             this, &Tray::resetSize);
    m_anchorAction          = mw_menu->addAction(QIcon(":/icons/pin-off"), tr("&Floating"),                                     this, &Tray::toggleAnchor);
    mw_menu->addSeparator();
    m_helpAction            = mw_menu->addAction(QIcon(":/icons/ic_help_outline_white_18dp"), tr("&Help/Settings"),             this, &Tray::help);
    m_quitAction            = mw_menu->addAction(QIcon(":/icons/ic_exit_to_app_white_18dp"), tr("&Quit"),                       this, &Tray::quit);

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

void Tray::toggleAnchor()
{
    m_anchored = !m_anchored;

    if(m_anchored) {
        m_anchorAction->setIcon(QIcon(":/icons/pin-off"));
        m_anchorAction->setText(tr("&Floating"));
    } else {
        m_anchorAction->setIcon(QIcon(":/icons/pin"));
        m_anchorAction->setText(tr("&Anchored"));
    }

    emit toggledAnchor(m_anchored);
}

bool Tray::anchored() const
{
    return m_anchored;
}

bool Tray::paused() const
{
    return m_paused;
}
