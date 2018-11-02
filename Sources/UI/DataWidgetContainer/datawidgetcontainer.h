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

#ifndef DATAWIDGETCONTAINER_H
#define DATAWIDGETCONTAINER_H

#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>

#include "../CoreUI/coreui.h"
#include "../ListWidget/abstractlistedwidget.h"
#include "../DataWidget/datawidget.h"
#include "../ListWidget/container.h"
#include "../SearchBox/searchbox.h"
#include "headerwidget.h"

class DataWidgetContainer : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidgetContainer(QWidget *parent = nullptr);

    Container *getContainer() const;

    SearchBox *searchBox() const;

signals:

public slots:
    void updateSearch(const Core::Filter &filter);

private:
    QVBoxLayout  *m_layout;

    QLabel       *mw_searchResult;

    SearchBox    *mw_search;
    HeaderWidget *mw_header;
    Container    *mw_container;
};

#endif // DATAWIDGETCONTAINER_H
