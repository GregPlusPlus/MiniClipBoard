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

#ifndef DATETIMEPICKER_H
#define DATETIMEPICKER_H

#include <QWidget>
#include <QLabel>
#include <QDateTimeEdit>
#include <QComboBox>

#include <QGridLayout>

#include "../../../Core/core.h"
#include "../../../Utils/utils.h"

class DateTimePicker : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimePicker(QWidget *parent = nullptr);
    Core::DateTimeFilter getDateTimeFilter();
signals:
    void dateTimeFilterChanged(const Core::DateTimeFilter &filter);

public slots:
    void updateMode(int index);
    void updateDateTimeFilter();

private:
    QGridLayout *m_layout;

    QComboBox *mw_mode;

    QDateTimeEdit *mw_dt_1;
    QDateTimeEdit *mw_dt_2;

    Core::DateTimeFilterType m_mode;
};

#endif // DATETIMEPICKER_H
