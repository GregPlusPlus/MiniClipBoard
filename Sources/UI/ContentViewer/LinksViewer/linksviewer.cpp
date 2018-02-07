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

#include "linksviewer.h"

LinksViewer::LinksViewer(const Core::Urls &urls, QWidget *parent) : QWidget(parent), m_urls(urls)
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);

    mw_container = new Container(this);

    m_layout->addWidget(mw_container);

    setLayout(m_layout);

    displayLinks();
}

void LinksViewer::displayLinks()
{
    for(int i = 0; i < m_urls.count(); i++) {
        LinkViewer *viewer = new LinkViewer(m_urls.at(i), this);

        mw_container->addWidget(viewer);
    }
}
