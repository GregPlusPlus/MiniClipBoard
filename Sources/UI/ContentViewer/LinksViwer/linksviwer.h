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

#ifndef LINKSVIWER_H
#define LINKSVIWER_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>

#include <QVBoxLayout>

#include <QDesktopServices>
#include <QFileInfo>

#include <QList>
#include <QUrl>

#include "../../../Core/core.h"

class LinksViwer : public QWidget
{
    Q_OBJECT
public:
    explicit LinksViwer(const Core::Urls &urls, QWidget *parent = nullptr);

signals:

public slots:

private:
    QLabel *mw_links;
    QScrollArea *mw_scroll;

    QVBoxLayout *m_layout;

private:
    QString getHtmlFromUrls(const Core::Urls &urls);
    QString getTextFromUrl(const QUrl &url);
};

#endif // LINKSVIWER_H
