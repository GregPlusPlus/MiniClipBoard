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

#include "linkviewer.h"

LinkViewer::LinkViewer(const Plugins::Plugins &plugins, const QUrl &url, QWidget *parent)
    : AbstractListedWidget(parent), m_plugins(plugins)
{
    //setStyleSheet("QWidget{border: 1px solid blue;}");

    //setFixedHeight(100);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_layout = new QGridLayout;
    m_layout->setContentsMargins(0, 10, 0, 0);

    mw_icon = new QLabel(this);
    mw_icon->setPixmap(QPixmap(":/icons/ic_link_white_24dp"));

    mw_link = new LinkButton(this);
    connect(mw_link, &LinkButton::clicked, [=]() {
        if(!QDesktopServices::openUrl(m_url)) {
            QMessageBox::critical(this, tr("Unable to access Url"),
                                  tr("Unable to access Url <i>%1</i><br><br>"
                                     "Maybe the file / folder was removed or the drive is not accessible.")
                                  .arg(m_url.toDisplayString()));
        }
    });

    mw_openBrowser = new FlatActionButton(QIcon(":/icons/ic_language_white_18dp"), tr("Open integrated browser"), this);
    connect(mw_openBrowser, &FlatActionButton::clicked, [=]() {
        emit openBrowser(m_url);
    });

    mw_viewButton = new FlatActionButton(QIcon(":/icons/ic_visibility_white_18dp"), tr("View"), this);
    connect(mw_viewButton, &FlatActionButton::clicked, [=]() {
        emit viewFile(m_url);
    });

    setUrl(url);

    m_layout->addWidget(mw_icon,                    0, 0, 1, 1);
    m_layout->addWidget(mw_openBrowser,             0, 1, 1, 1);
    m_layout->addWidget(mw_viewButton,              0, 2, 1, 1);
    m_layout->addWidget(mw_link,                    0, 3, 1, 1);
    m_layout->addWidget(UtilsUI::createSeparator(), 1, 0, 1, 4, Qt::AlignBottom);

    setLayout(m_layout);
}

LinkViewer::~LinkViewer()
{

}

void LinkViewer::setUrl(const QUrl &url)
{
    m_url = url;

    if(m_url.isLocalFile()) {
        mw_link->setText(QFileInfo(m_url.toString()).fileName());
        mw_link->setDescription(tr("From : %1").arg(QFileInfo(m_url.toString()).absoluteDir().dirName()));

        mw_icon->setPixmap(QPixmap(":/icons/ic_insert_drive_file_white_24dp"));

        mw_openBrowser->setVisible(false);

        mw_viewButton->setVisible(Core::isFileSupported(url, m_plugins));
    } else {
        mw_link->setText(m_url.toString());

        mw_openBrowser->setVisible(true);

        mw_viewButton->setVisible(false);
    }

    m_layout->update();
}

void LinkViewer::removeWidget()
{
    emit removed(this);
}

void LinkViewer::fadeIn() {}

void LinkViewer::fadeOut() {}
