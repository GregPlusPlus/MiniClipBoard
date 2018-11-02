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

#ifndef COPYTOOLTIPWINDOW_H
#define COPYTOOLTIPWINDOW_H

#include <QWidget>

#include <QHBoxLayout>

#include "../../Core/Core/core.h"
#include "../../Core/PrintManager/printmanager.h"
#include "../CoreUI/Widgets/flatactionbutton.h"
#include "../CoreUI/Widgets/tooltipwindow.h"

class CopyTooltipWindow : public TooltipWindow
{
    Q_OBJECT

public:
    explicit CopyTooltipWindow(const Core::ClipboardData &data, QWidget *parent = nullptr);

signals:
    void removeData(const Core::ClipboardData &data);

public slots:

private:
    QHBoxLayout      *m_layout;

    FlatActionButton *mw_closeButton;
    FlatActionButton *mw_saveButton;
    FlatActionButton *mw_printButton;
    FlatActionButton *mw_removeButton;

    Core::ClipboardData m_data;
};

#endif // COPYTOOLTIPWINDOW_H
