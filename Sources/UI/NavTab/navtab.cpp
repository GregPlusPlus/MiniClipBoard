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

#include "navtab.h"

NavTab::NavTab(QWidget *parent) : QWidget(parent)
{
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

void NavTab::addTab(const QIcon &normalIcon, const QIcon &highlightedIcon, const QString &tooltipText, QWidget *widget)
{
    addButton(normalIcon, highlightedIcon, widget)->setToolTip(tooltipText);
}

void NavTab::addTab(const QIcon &normalIcon, const QIcon &highlightedIcon, QWidget *widget)
{
    addButton(normalIcon, highlightedIcon, widget);
}

TabButton *NavTab::addButton(const QIcon &normalIcon, const QIcon &highlightedIcon, QWidget *widget)
{
    TabButton *button = new TabButton(this);
    button->setIconNormal(normalIcon);
    button->setIconHighlighted(highlightedIcon);
    button->setFlat(true);
    button->setIndex(m_tabs.count());
    connect(button, &TabButton::buttonSelected, this, &NavTab::select);

    Tab tab(button, widget, m_tabs.count());

    m_tabs.append(tab);

    m_tabslayout->addWidget(button);
    mw_stack->addWidget(widget);

    select(m_tabs.count() - 1);

    m_currentTab = tab;

    return button;
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
