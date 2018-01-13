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

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QScrollArea>
#include <QSpacerItem>

#include <QVBoxLayout>

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QBitmap>

#include <QList>

#include <QDebug>

#include "../ListWidget/abstractlistedwidget.h"

class Container : public QScrollArea
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);

    QList<AbstractListedWidget *> widgets() const;

signals:
    void widgetAdded(QWidget *widget);
    void widgetRemoved(QWidget *widget);

public slots:
    void addWidget(AbstractListedWidget *widget);
    void removeWidget(AbstractListedWidget *widget);
    void clear();

private:
    QVBoxLayout *m_layout;
    QWidget *mw_widget;
    QSpacerItem *m_spacer;

    QList<AbstractListedWidget *> m_widgets;
};

#endif // CONTAINER_H
