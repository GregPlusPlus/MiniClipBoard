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

#ifndef COREUI_H
#define COREUI_H

#include <QWidget>

#include <QUuid>

#include <QList>

#include "../../Core/core.h"
#include "../DataWidget/datawidget.h"

namespace CoreUI
{
    DataWidget *copyDataWidget(DataWidget *widget, QWidget *parent);
    AbstractListedWidget *getWidgetFromUUID(const QList<AbstractListedWidget *> &widgets, const QUuid &uuid);
    int filterDataWidgets(const Core::Filter &filter, QList<AbstractListedWidget *> widgets);
}

#endif // COREUI_H
