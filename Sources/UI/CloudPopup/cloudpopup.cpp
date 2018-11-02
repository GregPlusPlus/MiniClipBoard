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

#include "cloudpopup.h"

CloudPopup::CloudPopup() : InfosPopup()
{
    m_layout = new QStackedLayout;

    mw_selector = new PlatformSelector(this);
    connect(mw_selector, &PlatformSelector::platformSelected, this, &CloudPopup::platformSelected);

    mw_pastebin = new PastebinSettings(this);
    connect(mw_pastebin, &PastebinSettings::send, [=](CloudTypes::CloudData &data) {
        hide();
        m_layout->setCurrentWidget(mw_selector);
        emit upload(data);
    });
    connect(mw_pastebin, &PastebinSettings::cancel, [=]() {
        m_layout->setCurrentWidget(mw_selector);
    });

    m_layout->addWidget(mw_selector);
    m_layout->addWidget(mw_pastebin);

    setLayout(m_layout);
}

void CloudPopup::platformSelected(int platform)
{
    if(platform == CloudTypes::Cloud_Platform_Pastebin) {
        mw_pastebin->checkKey();
        m_layout->setCurrentWidget(mw_pastebin);
    }
}
