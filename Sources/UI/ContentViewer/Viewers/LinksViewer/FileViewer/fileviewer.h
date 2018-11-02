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

#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>
#include <QLabel>

#include <QGridLayout>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QDebug>

#include "../../../../../Core/Core/core.h"
#include "../../../../CoreUI/Widgets/flatactionbutton.h"
#include "../../Plugins/pluginsutils.h"

#include "../../ImageViewer/imageviewer.h"
#include "../../HTMLViewer/htmlviewer.h"
#include "../../TextViewer/textviewer.h"

#include "../../../../Browser/browser.h"

#include "errorwidget.h"

class FileViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FileViewer(const QUrl &url, const Plugins::Plugins &plugins, QWidget *parent = nullptr);

signals:
    void closeViewer(FileViewer *viewer);

public slots:
    void show();

private:
    QGridLayout *m_layout;
    QWidget *mw_viewer = nullptr;
    QPushButton *mw_closeButton;

    Plugins::Plugins m_plugins;

private:
    void setViewer(const QUrl &url);
    QWidget *searchPluginsWidget(const QUrl &url);
};

#endif // FILEVIEWER_H
