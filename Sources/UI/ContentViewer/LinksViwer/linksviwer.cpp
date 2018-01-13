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

#include "linksviwer.h"

LinksViwer::LinksViwer(const Core::Urls &urls, QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);

    mw_scroll = new QScrollArea(this);
    mw_scroll->setWidgetResizable(true);
    mw_scroll->setAttribute(Qt::WA_TranslucentBackground);

    mw_links = new QLabel(getHtmlFromUrls(urls), this);
    mw_links->setStyleSheet("background: transparent; padding-top: 20px;");
    mw_links->setAlignment(Qt::AlignTop);
    connect(mw_links, &QLabel::linkActivated, [=](const QString &link) {
        QDesktopServices::openUrl(QUrl(link));
    });

    QFont fontData = mw_links->font();
    fontData.setBold(true);
    fontData.setPixelSize(15);
    mw_links->setFont(fontData);

    mw_scroll->setWidget(mw_links);

    m_layout->addWidget(mw_scroll);

    setLayout(m_layout);
}

QString LinksViwer::getHtmlFromUrls(const Core::Urls &urls)
{
    QString str = "<ul>";

    for(int i = 0; i < urls.count(); i++) {
        str += QString("<li><a href=\"%1\" id=\"%2\" style=\"color: #D1DBE6;\">%3</a><hr><li>").arg(urls.at(i).toString()).arg(i).arg(getTextFromUrl(urls.at(i)));
    }

    str += "</ul>";

    return str;
}

QString LinksViwer::getTextFromUrl(const QUrl &url)
{
    QString strurl = url.toString();

    if(strurl.contains("file:///")) {
        return tr("File : ") + QFileInfo(strurl).fileName();
    } else {
        return strurl;
    }
}
