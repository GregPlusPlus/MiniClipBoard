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

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpacerItem>

#include <QVBoxLayout>

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QBitmap>

#include <QList>

#include <QResizeEvent>

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
    void widgetsCountChanged(int count);

public slots:
    void addWidget(AbstractListedWidget *widget);
    AbstractListedWidget *removeWidget(AbstractListedWidget *widget);
    void clear();
    void updateShadow();

private:
    QVBoxLayout *m_layout;

    QWidget     *mw_widget;
    QWidget     *mw_shadow;

    QSpacerItem *m_spacer;

    QList<AbstractListedWidget *> m_widgets;

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CONTAINER_H
