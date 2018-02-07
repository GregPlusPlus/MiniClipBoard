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

#include "datetimepicker.h"

DateTimePicker::DateTimePicker(QWidget *parent) : QWidget(parent)
{
    m_mode = Core::DateTimeFilterType_None;

    m_layout = new QGridLayout;

    mw_mode = new QComboBox(this);
    mw_mode->addItem(tr("None"));
    mw_mode->addItem(tr("Before"));
    mw_mode->addItem(tr("After"));
    mw_mode->addItem(tr("Between"));
    mw_mode->setCurrentIndex(0);
    connect(mw_mode, SIGNAL(activated(int)), this, SLOT(updateMode(int)));

    mw_dt_1 = new QDateTimeEdit(this);
    mw_dt_1->setAccelerated(true);
    mw_dt_1->setDisplayFormat(tr("dd/MM/yyyy hh:mm:ss"));
    mw_dt_2 = new QDateTimeEdit(this);
    mw_dt_2->setAccelerated(true);
    mw_dt_2->setDisplayFormat(tr("dd/MM/yyyy hh:mm:ss"));

    connect(mw_dt_1, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(updateDateTimeFilter()));
    connect(mw_dt_2, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(updateDateTimeFilter()));

    m_layout->addWidget(mw_mode);
    m_layout->addWidget(new QLabel(tr("From :")));
    m_layout->addWidget(mw_dt_1);
    m_layout->addWidget(new QLabel(tr("To :")));
    m_layout->addWidget(mw_dt_2);

    setLayout(m_layout);

    updateMode(0);
}

Core::DateTimeFilter DateTimePicker::getDateTimeFilter()
{
    return Core::DateTimeFilter(m_mode, mw_dt_1->dateTime(), mw_dt_2->dateTime());
}

void DateTimePicker::updateMode(int index)
{
    switch (index) {
    case 0:
        mw_dt_1->setEnabled(false);
        mw_dt_2->setEnabled(false);
        m_mode =  Core::DateTimeFilterType_None;
        break;
    case 1:
        mw_dt_1->setEnabled(false);
        mw_dt_2->setEnabled(true);
        m_mode =  Core::DateTimeFilterType_Before;
        break;
    case 2:
        mw_dt_1->setEnabled(true);
        mw_dt_2->setEnabled(false);
        m_mode =  Core::DateTimeFilterType_After;
        break;
    case 3:
        mw_dt_1->setEnabled(true);
        mw_dt_2->setEnabled(true);
        m_mode =  Core::DateTimeFilterType_Between;
        break;
    default:
        return;
        break;
    }

    updateDateTimeFilter();
}

void DateTimePicker::updateDateTimeFilter()
{
    emit dateTimeFilterChanged(Core::DateTimeFilter(m_mode, mw_dt_1->dateTime(), mw_dt_2->dateTime()));
}
