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

#include "navtab.h"

NavTab::NavTab(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(0);

    m_tabslayout = new QHBoxLayout;
    m_tabslayout->setSpacing(0);
    m_tabslayout->setMargin(0);

    mw_stack = new QStackedWidget(this);

    m_mainLayout->addWidget(mw_stack);
    m_mainLayout->addLayout(m_tabslayout);

    setLayout(m_mainLayout);
}

void NavTab::addTab(const QIcon &icon, const QString &tooltipText, QWidget *widget)
{
    TabButton *button = new TabButton(this);
    button->setIcon(icon);
    button->setToolTip(tooltipText);
    button->setFlat(true);
    button->setIndex(m_tabs.count());
    connect(button, SIGNAL(buttonSelected(int)), this, SLOT(select(int)));

    Tab tab(button, widget, m_tabs.count());

    m_tabs.append(tab);

    m_tabslayout->addWidget(button);
    mw_stack->addWidget(widget);

    select(m_tabs.count() - 1);

    m_currentTab = tab;
}

void NavTab::addTab(const QIcon &icon, QWidget *widget)
{
    TabButton *button = new TabButton(this);
    button->setIcon(icon);
    button->setFlat(true);
    button->setIndex(m_tabs.count());
    connect(button, SIGNAL(buttonSelected(int)), this, SLOT(select(int)));

    Tab tab(button, widget, m_tabs.count());

    m_tabs.append(tab);

    m_tabslayout->addWidget(button);
    mw_stack->addWidget(widget);

    select(m_tabs.count() - 1);

    m_currentTab = tab;
}

void NavTab::select(int index)
{
    if(index < 0 || index > m_tabs.count() - 1) {
        return;
    }

    if(m_currentTab.button) {
        m_currentTab.button->setSelected(false);
    }

    m_currentTab = m_tabs.at(index);

    m_currentTab.button->setSelected(true);

    mw_stack->setCurrentIndex(index);
}
