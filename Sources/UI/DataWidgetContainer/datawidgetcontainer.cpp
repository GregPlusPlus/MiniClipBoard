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

#include "datawidgetcontainer.h"

DataWidgetContainer::DataWidgetContainer(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    mw_search = new SearchBox(this);
    connect(mw_search, &SearchBox::filterChanged, this, &DataWidgetContainer::updateSearch);

    mw_searchResult = new QLabel(this);
    mw_searchResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mw_searchResult->setFixedHeight(30);
    mw_searchResult->setAlignment(Qt::AlignCenter);
    mw_searchResult->setVisible(false);
    mw_searchResult->setStyleSheet("font: bold 15px;"
                                   "background: #242D35;"
                                   "border-bottom: 1px solid #19232D;");

    mw_header = new HeaderWidget(this);

    mw_container = new Container(this);
    connect(mw_container, &Container::widgetAdded, [=]() {
        updateSearch(mw_search->getFilter());
    });
    connect(mw_container, &Container::widgetsCountChanged, [=](int count) {
        mw_header->setVisible(!count);
    });

    m_layout->addWidget(mw_search);
    m_layout->addWidget(mw_header);
    m_layout->addWidget(mw_searchResult);
    m_layout->addWidget(mw_container);

    setLayout(m_layout);
}

Container *DataWidgetContainer::getContainer() const
{
    return mw_container;
}

void DataWidgetContainer::updateSearch(const Core::Filter &filter)
{
    if(filter.text.isEmpty() &&
            filter.type == Core::MimeType_None &&
            filter.dateTimeFilter.type == Core::DateTimeFilterType_None) {
        mw_searchResult->setVisible(false);
    } else {
        mw_searchResult->setVisible(true);
    }

    mw_searchResult->setText(tr("Searching..."));

    int count = CoreUI::filterDataWidgets(filter, mw_container->widgets());

    if(!count) {
        mw_searchResult->setText(tr("<i>No data were found.</i>"));
    } else if(count == 1){
        mw_searchResult->setText(tr("1 result found."));
    } else {
        mw_searchResult->setText(tr("%1 results found.").arg(count));
    }
}

SearchBox *DataWidgetContainer::searchBox() const
{
    return mw_search;
}
