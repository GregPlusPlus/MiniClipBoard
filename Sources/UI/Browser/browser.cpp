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

#include "browser.h"

Browser::Browser(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("MiniClipBoard integrated browser"));

    connect(qApp, &QApplication::aboutToQuit, this, &Browser::cleanClose);

    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);

    mw_navBar = new NavBar(this);
    connect(mw_navBar, &NavBar::openExternal, [=]() {
        QDesktopServices::openUrl(mw_view->url());
    });
    connect(mw_navBar, &NavBar::closeBrowser, [=]() {
        emit closeBrowser(this);
        deleteLater();
    });

    mw_view = new QWebEngineView(this);
    connect(mw_view, &QWebEngineView::urlChanged, mw_navBar, &NavBar::setUrl);
    connect(mw_view, &QWebEngineView::iconChanged, mw_navBar, &NavBar::setIcon);
    connect(mw_view, &QWebEngineView::titleChanged, [=](const QString &title) {
        m_lastTitle = title;
        mw_navBar->setTitle(title);
        setWindowTitle(tr("MiniClipBoard integrated browser - %1").arg(title));
    });
    connect(mw_view, &QWebEngineView::loadStarted, [=]() {
        mw_status->setVisible(true);
        mw_status->setText(tr("Loading..."));
        mw_navBar->setTitle(tr("Loading..."));
        mw_navBar->setLoading();
    });
    connect(mw_view, &QWebEngineView::loadFinished, [=]() {
        mw_status->setVisible(false);
        mw_navBar->enableBack(mw_view->history()->canGoBack());
        mw_navBar->enableForward(mw_view->history()->canGoForward());
        mw_navBar->setTitle(m_lastTitle);
    });
    connect(mw_view, &QWebEngineView::loadProgress, [=](int progress) {
        mw_status->setText(tr("Loading... %1%").arg(progress));
    });

    connect(mw_navBar, &NavBar::urlEntered, [=](const QUrl &url) {
        mw_view->setUrl(url);
    });
    connect(mw_navBar, &NavBar::backward, mw_view, &QWebEngineView::back);
    connect(mw_navBar, &NavBar::forward,  mw_view, &QWebEngineView::forward);
    connect(mw_navBar, &NavBar::refresh,  mw_view, &QWebEngineView::reload);

    mw_status = new QLabel(this);
    mw_status->setVisible(false);
    mw_status->setFixedHeight(20);
    mw_status->setStyleSheet("padding-bottom: 8px;padding-left: 3px;");

    m_layout->addWidget(mw_navBar);
    m_layout->addWidget(mw_view);
    m_layout->addWidget(mw_status);

    setLayout(m_layout);
}

Browser::~Browser()
{
    disconnect(qApp, &QApplication::aboutToQuit, this, &Browser::cleanClose);
}

void Browser::setUrl(const QUrl &url)
{
    mw_view->setUrl(url);

    QThread::msleep(10); // REMINDME BUG : Used to fix a bug when the browser freezes, should be removed later
}

void Browser::cleanClose()
{
    if(mw_view) {
        delete mw_view;
        mw_view = nullptr;
    }
}

int Browser::controls() const
{
    return mw_navBar->controls();
}

void Browser::setControls(int flags)
{
    mw_navBar->setControls(flags);
    mw_navBar->setVisible((bool)flags);
}

void Browser::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);

    deleteLater();
}
