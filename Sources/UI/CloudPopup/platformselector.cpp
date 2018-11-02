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

#include "platformselector.h"

PlatformSelector::PlatformSelector(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;

    mw_pastebin = new QCommandLinkButton(tr("Pastebin"), tr("New paste"), this);
    mw_pastebin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(mw_pastebin, &QCommandLinkButton::clicked, [=]() {
        emit platformSelected(CloudTypes::Cloud_Platform_Pastebin);
    });

    m_layout->addWidget(mw_pastebin);
    m_layout->addStretch(1);

    setLayout(m_layout);
}
