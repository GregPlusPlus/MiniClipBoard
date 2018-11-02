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

#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>

#include <QPixmap>
#include <QMovie>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QDebug>

class IconWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IconWidget(QWidget *parent = nullptr);

signals:
    void clicked();

public slots:
    void setPixmap(const QPixmap &pixmap);
    void setMovie(QMovie *movie);
    void updateMovieFrame();

private:
    QPixmap m_currentPixmap;
    QMovie  *m_movie = nullptr;

protected:
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *event);
};

#endif // ICONWIDGET_H
