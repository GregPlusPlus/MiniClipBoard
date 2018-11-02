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

#ifndef LINKSVIWER_H
#define LINKSVIWER_H

#include <QWidget>
#include <QStackedWidget>

#include <QVBoxLayout>

#include <QMessageBox>

#include <QUrl>

#include <QDebug>

#include "../../../../Core/Core/core.h"
#include "../../plugins/pluginsutils.h"
#include "../../../../UI/ListWidget/abstractlistedwidget.h"
#include "../../../../UI/ListWidget/container.h"
#include "../../../../UI/Browser/browser.h"
#include "FileViewer/fileviewer.h"
#include "linkviewer.h"

class LinksViewer : public QWidget
{
    Q_OBJECT

public:
    explicit LinksViewer(const Core::Urls &urls, const Plugins::Plugins &plugins, QWidget *parent = nullptr);

signals:

public slots:
    void openBrowser(const QUrl &url);
    void viewFile(const QUrl &url);

private:
    QVBoxLayout      *m_layout;

    QStackedWidget   *mw_stacked;

    Container        *mw_container;

    Core::Urls m_urls;

    Plugins::Plugins m_plugins;

private:
    void displayLinks();
};

#endif // LINKSVIWER_H
