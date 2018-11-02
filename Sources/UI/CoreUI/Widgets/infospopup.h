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

#ifndef INFOSPOPUP_H
#define INFOSPOPUP_H

#include <QApplication>
#include <QWidget>
#include <QEvent>

#include <QPainter>

#include <QDebug>

#include "../coreui.h"

class InfosPopup : public QWidget
{
    Q_OBJECT
public:
    enum Side {
        Side_Top,
        Side_Bottom
    };

public:
    explicit InfosPopup(Side side = Side_Bottom, QWidget *parent = nullptr);

    void setLayout(QLayout *layout);
    void setAnchorWidget(QWidget *anchor);
    void cleanDestroy();

    Side side() const;

signals:

public slots:
    void moveToPoint(const QPoint &point);
    void updatePopupPos();
    void setVisible(bool visible);
    void trigger();
    void setSide(const Side &side);

private:
    QWidget *mw_container;
    QWidget *mw_anchor = nullptr;

    QPoint m_point;
    int m_indicatorSize = 12;

    bool m_triggered = false;

    Side m_side;

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // INFOSPOPUP_H
