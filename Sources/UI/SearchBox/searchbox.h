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

#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

#include <QMenu>
#include <QWidgetAction>
#include <QActionGroup>
#include <QAction>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QPaintEvent>

#include <QDebug>

#include "../../Core/Core/core.h"
#include "../CoreUI/Widgets/lineedit.h"
#include "../../Utils/utils.h"
#include "../UtilsUI/utilsui.h"
#include "DateTimePicker/datetimepicker.h"

class SearchBox : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = nullptr);
    Core::Filter getFilter();

    int getTopCrop() const;
    void setTopCrop(int topCrop);

signals:
    void filterChanged(const Core::Filter &filter);

public slots:
    void setText(const QString &text);

private:
    LineEdit        *mw_search;
    QPushButton     *mw_clearButton;
    QPushButton     *mw_optionsButton;
    QMenu           *mw_menu;
    QActionGroup    *mw_group;

    QCheckBox       *mw_caseSensitive;

    QAction         *m_filterAll;
    QAction         *m_filterImage;
    QAction         *m_filterColor;
    QAction         *m_filterHtml;
    QAction         *m_filterText;
    QAction         *m_filterURL;

    DateTimePicker  *mw_dateTimePicker;

    Core::MimeType m_filterType = Core::MimeType_None;

    int m_topCrop = 0;

private:
    void buildMenu();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SEARCHBOX_H
