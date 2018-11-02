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

#include "linksviewer.h"

LinksViewer::LinksViewer(const Core::Urls &urls, const Plugins::Plugins &plugins, QWidget *parent)
    : QWidget(parent), m_urls(urls), m_plugins(plugins)
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);

    mw_stacked = new QStackedWidget(this);
    m_layout->addWidget(mw_stacked);
    setLayout(m_layout);

    mw_container = new Container(mw_stacked);

    mw_stacked->addWidget(mw_container);

    displayLinks();
}

void LinksViewer::openBrowser(const QUrl &url)
{
    Browser *browser = new Browser(this);

    browser->setControls(NavBar::Controls_Close | NavBar::Controls_Navigate | NavBar::Controls_Url | NavBar::Controls_External);

    connect(browser, &Browser::closeBrowser, [=](Browser *w) {
        mw_stacked->removeWidget(w);
    });

    browser->setUrl(url);

    mw_stacked->addWidget(browser);
    mw_stacked->setCurrentWidget(browser);
}

void LinksViewer::viewFile(const QUrl &url)
{
    FileViewer *viewer = new FileViewer(url, m_plugins, this);

    connect(viewer, &FileViewer::closeViewer, [=](FileViewer *viewer) {
        mw_stacked->removeWidget(viewer);
    });

    mw_stacked->addWidget(viewer);
    mw_stacked->setCurrentWidget(viewer);
}

void LinksViewer::displayLinks()
{
    for(QUrl url : m_urls) {
        LinkViewer *w = new LinkViewer(m_plugins, url, this);
        connect(w, &LinkViewer::openBrowser, this, &LinksViewer::openBrowser);
        connect(w, &LinkViewer::viewFile, this, &LinksViewer::viewFile);
        mw_container->addWidget(w);
    }
}
