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

#include "container.h"

Container::Container(QWidget *parent) : QScrollArea(parent)
{
    setWidgetResizable(true);
    setAutoFillBackground(true);
    setAcceptDrops(true);

    mw_widget = new QWidget(this);
    mw_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layout = new QVBoxLayout;
    m_layout->setSpacing(0);
    mw_widget->setLayout(m_layout);

    m_spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_layout->addSpacerItem(m_spacer);

    setWidget(mw_widget);
}

void Container::addWidget(AbstractListedWidget *widget)
{
    connect(widget, SIGNAL(removed(AbstractListedWidget*)), this, SLOT(removeWidget(AbstractListedWidget*)));
    m_widgets.append(widget);
    m_layout->insertWidget(0, widget);

    widget->show();
    widget->setAnimationDuration(400);
    widget->fadeIn();

    emit widgetAdded(widget);
}

void Container::removeWidget(AbstractListedWidget *widget)
{
    m_layout->removeWidget(widget);

    for(int i = 0; i < m_widgets.count(); i++) {
        if(m_widgets.at(i) == widget) {
            m_layout->removeWidget(widget);
            m_widgets.removeAt(i);
            emit widgetRemoved(widget);
            return;
        }
    }
}

void Container::clear()
{
    for(int i = 0; i < m_widgets.count(); i++) {
        if(m_widgets.at(i)){
            m_layout->removeWidget(m_widgets.at(i));
            emit widgetRemoved(m_widgets.at(i));
        }
    }

    m_widgets.clear();
}

QList<AbstractListedWidget *> Container::widgets() const
{
    return m_widgets;
}
