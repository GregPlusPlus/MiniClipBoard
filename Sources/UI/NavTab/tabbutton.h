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

#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QPushButton>

#include <QPropertyAnimation>

#include <QPainter>
#include <Qpen>
#include <QBrush>

#include <QPaintEvent>

#include <QDebug>

class TabButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int fade READ fade WRITE setFade)

public:
    explicit TabButton(QWidget *parent = nullptr);

    int index() const;
    void setIndex(int index);

    bool selected() const;
    void setSelected(bool selected);
    void setSelected(bool selected, bool animated);

    int fade() const;
    void setFade(int fade);

signals:
    void buttonSelected(int index);

public slots:
    void setIconNormal(const QIcon &icon);
    void setIconHighlighted(const QIcon &icon);

private:
    int m_index;

    bool m_selected;
    bool m_mousePress;

    int m_fade;

    QIcon m_normalIcon;
    QIcon m_highlightedIcon;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void putIcon();

    void fadeIn(int duration);
    void fadeOut(int duration);
};

#endif // TABBUTTON_H
