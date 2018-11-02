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

#include "navbar.h"

NavBar::NavBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(50);

    m_loadingAnimation = new QMovie(":/animations/loading");

    m_layout = new QHBoxLayout;

    mw_close = new FlatActionButton(QIcon(":/icons/ic_clear_white_18dp"), tr("Close"), this);
    connect(mw_close, &FlatActionButton::clicked, this, &NavBar::closeBrowser);

    mw_backward = new QPushButton(QIcon(":/icons/ic_arrow_back_white_18dp"), QString(), this);
    mw_backward->setToolTip(tr("Back"));
    mw_backward->setEnabled(false);
    mw_backward->setShortcut(QKeySequence::Back);
    connect(mw_backward, &QPushButton::clicked, this, &NavBar::backward);

    mw_refresh = new QPushButton(QIcon(":/icons/ic_refresh_white_18dp"), QString(), this);
    mw_refresh->setToolTip(tr("Refresh"));
    mw_refresh->setShortcut(QKeySequence("Ctrl+R"));
    connect(mw_refresh, &QPushButton::clicked, this, &NavBar::refresh);

    mw_forward = new QPushButton(QIcon(":/icons/ic_arrow_forward_white_18dp"), QString(), this);
    mw_forward->setToolTip(tr("Forward"));
    mw_forward->setEnabled(false);
    mw_forward->setShortcut(QKeySequence::Forward);
    connect(mw_forward, &QPushButton::clicked, this, &NavBar::forward);

    mw_url = new URLBar(this);
    connect(mw_url->iconWidget(), &IconWidget::clicked, this, &NavBar::showDetails);
    connect(mw_url, &URLBar::returnPressed, [=]() {
        if(!mw_url->text().startsWith("http://") && !mw_url->text().startsWith("https://")) {
            mw_url->setText("http://" + mw_url->text());
        }

        emit urlEntered(QUrl(mw_url->text()));
    });

    mw_external = new FlatActionButton(QIcon(":/icons/ic_open_in_new_white_18dp"), tr("Open external browser"));
    connect(mw_external, &FlatActionButton::clicked, this, &NavBar::openExternal);

    m_layout->addWidget(mw_close);
    m_layout->addWidget(mw_backward);
    m_layout->addWidget(mw_refresh);
    m_layout->addWidget(mw_forward);
    m_layout->addWidget(mw_url);
    m_layout->addWidget(mw_external);

    mw_popup = new Popup;
    mw_popup->setAnchorWidget(mw_url->iconWidget());
    mw_popup->hide();
    mw_popup->setWindowOpacity(.9);

    setLayout(m_layout);

    setUrl(QUrl("about:blank"));
}

NavBar::~NavBar()
{
    mw_popup->cleanDestroy();
}

void NavBar::setUrl(const QUrl &url)
{
    mw_url->setText(url.toString());
    mw_url->home(0);
}

void NavBar::setIcon(const QIcon &icon)
{
    if(icon.isNull()) {
        mw_url->iconWidget()->setPixmap(QPixmap(":/icons/outline_insert_drive_file_white_18dp"));
    } else {
        mw_url->iconWidget()->setPixmap(icon.pixmap(20, 20));
    }
}

void NavBar::setTitle(const QString &title)
{
    mw_url->iconWidget()->setToolTip(title);
    mw_popup->setTitle(title);
    mw_popup->setHttpsUse(mw_url->text().startsWith("https://"));
}

void NavBar::setLoading()
{
    mw_url->iconWidget()->setMovie(m_loadingAnimation);
    m_loadingAnimation->start();
}

void NavBar::enableBack(bool enabled)
{
    mw_backward->setEnabled(enabled);
}

void NavBar::enableForward(bool enabled)
{
    mw_forward->setEnabled(enabled);
}

void NavBar::showDetails()
{
    mw_popup->trigger();
}

int NavBar::controls() const
{
    return m_controls;
}

void NavBar::setControls(int flags)
{
    m_controls = flags;

    if((m_controls & Controls_Close) != 0) {
        mw_close->setVisible(true);
    } else {
        mw_close->setVisible(false);
    }

    if((m_controls & Controls_Navigate) != 0) {
        mw_backward->setVisible(true);
        mw_forward->setVisible(true);
    } else {
        mw_backward->setVisible(false);
        mw_forward->setVisible(false);
    }

    if((m_controls & Controls_Refresh) != 0) {
        mw_refresh->setVisible(true);
    } else {
        mw_refresh->setVisible(false);
    }

    if((m_controls & Controls_Url) != 0) {
        mw_url->setVisible(true);
    } else {
        mw_url->setVisible(false);
    }

    if((m_controls & Controls_Url) != 0) {
        mw_external->setVisible(true);
    } else {
        mw_external->setVisible(false);
    }
}
