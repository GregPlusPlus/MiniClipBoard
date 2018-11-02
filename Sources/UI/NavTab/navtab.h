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

#ifndef NAVTAB_H
#define NAVTAB_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QIcon>

#include <QList>

#include <QDebug>

#include "tabbutton.h"

class NavTab : public QWidget
{
    Q_OBJECT

public:
    struct Tab
    {
        Tab(){}
        Tab(TabButton *_button, QWidget *_widget, int _index) : button(_button), widget(_widget), tabIndex(_index){}
        TabButton *button = nullptr;
        QWidget *widget = nullptr;
        int tabIndex = 0;
    };

public:
    explicit NavTab(QWidget *parent = nullptr);

signals:

public slots:
    void addTab(const QIcon &normalIcon, const QIcon &highlightedIcon, const QString &tooltipText, QWidget *widget);
    void addTab(const QIcon &normalIcon, const QIcon &highlightedIcon, QWidget *widget);
    void select(int index);

private:
    QVBoxLayout    *m_mainLayout;
    QHBoxLayout    *m_tabslayout;

    QStackedWidget *mw_stack;

    QList<Tab> m_tabs;
    Tab m_currentTab;

private :
    TabButton *addButton(const QIcon &normalIcon, const QIcon &highlightedIcon, QWidget *widget);
};

#endif // NAVTAB_H
