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

#include "popup.h"

Popup::Popup() : InfosPopup()
{
    m_layout = new QGridLayout;

    mw_title    = new QLabel(this);
    mw_security = new QLabel(this);

    m_layout->addWidget(mw_title,    0, 0, 1, 1);
    m_layout->addWidget(mw_security, 1, 0, 1, 1);

    setLayout(m_layout);
}

void Popup::setTitle(const QString &title)
{
    mw_title->setText(title);
    adjustSize();

    updateGeometry();
}

void Popup::setHttpsUse(bool use)
{
    if(use) {
        mw_security->setText(tr("🔒 This site uses HTTPS"));
    } else {
        mw_security->setText(tr("⚠ This site DO NOT uses HTTPS"));
    }

    updateGeometry();
}
