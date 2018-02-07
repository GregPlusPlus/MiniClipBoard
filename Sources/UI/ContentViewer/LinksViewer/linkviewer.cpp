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

#include "linkviewer.h"

LinkViewer::LinkViewer(const QUrl &url, QWidget *parent) : AbstractListedWidget(parent)
{
    //setStyleSheet("QWidget{border: 1px solid blue;}");

    //setFixedHeight(100);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_layout = new QGridLayout;
    m_layout->setContentsMargins(0, 10, 0, 0);

    mw_icon = new QLabel(this);
    mw_icon->setPixmap(QPixmap(":/icons/ic_link_white_24dp"));

    mw_link = new QCommandLinkButton(this);
    mw_link->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mw_link->setFlat(true);
    mw_link->setCursor(Qt::PointingHandCursor);
    mw_link->setIcon(QIcon(":/icons/arrow_link"));
    connect(mw_link, &QCommandLinkButton::clicked, [=]() {
        QDesktopServices::openUrl(m_url);
    });

    setUrl(url);

    m_layout->addWidget(mw_icon, 0, 0, 1, 1);
    m_layout->addWidget(mw_link, 0, 1, 1, 1);
    m_layout->addWidget(UtilsUI::createSeparator(), 1, 0, 1, 2, Qt::AlignBottom);

    setLayout(m_layout);
}

LinkViewer::~LinkViewer()
{

}

void LinkViewer::setUrl(const QUrl &url)
{
    m_url = url;

    if(m_url.toString().startsWith("file:///")) {
        mw_link->setText(QFileInfo(m_url.toString()).fileName());
        mw_link->setDescription(tr("From : %1").arg(QFileInfo(m_url.toString()).absoluteDir().dirName()));
        mw_icon->setPixmap(QPixmap(":/icons/ic_insert_drive_file_white_24dp"));
    } else {
        mw_link->setText(m_url.toString());
    }
}

void LinkViewer::removeWidget()
{
    emit removed(this);
}

void LinkViewer::fadeIn() {}

void LinkViewer::fadeOut() {}
