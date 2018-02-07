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

#ifndef LINKVIEWER_H
#define LINKVIEWER_H

#include <QWidget>
#include <QCommandLinkButton>
#include <QPushButton>
#include <QLabel>

#include <QGridLayout>

#include <QUrl>

#include <QDesktopServices>

#include <QFileInfo>
#include <QDir>

#include <QDebug>

#include "../../../UI/ListWidget/abstractlistedwidget.h"
#include "../../UtilsUI/utilsui.h"

class LinkViewer : public AbstractListedWidget
{
    Q_OBJECT
public:
    explicit LinkViewer(const QUrl &url = QUrl(), QWidget *parent = nullptr);
    ~LinkViewer();

signals:

public slots:
    void setUrl(const QUrl &url);
    void removeWidget();
    void fadeIn();
    void fadeOut();

private:
    QGridLayout *m_layout;

    QLabel *mw_icon;
    QCommandLinkButton *mw_link;

    QUrl m_url;
};

#endif // LINKVIEWER_H
