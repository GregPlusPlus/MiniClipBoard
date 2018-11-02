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

#include "iconwidget.h"

IconWidget::IconWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(20, 20);
    setCursor(Qt::PointingHandCursor);
}

void IconWidget::setPixmap(const QPixmap &pixmap)
{
    m_currentPixmap = pixmap;

    if(m_movie) {
        disconnect(m_movie, &QMovie::frameChanged, this, &IconWidget::updateMovieFrame);
    }

    update();
}

void IconWidget::setMovie(QMovie *movie)
{
    if(m_movie) {
        disconnect(m_movie, &QMovie::frameChanged, this, &IconWidget::updateMovieFrame);
    }

    m_movie = movie;
    connect(m_movie, &QMovie::frameChanged, this, &IconWidget::updateMovieFrame);
}

void IconWidget::updateMovieFrame()
{
    m_currentPixmap = m_movie->currentPixmap();
    update();
}

void IconWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit clicked();
}

void IconWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);

    p.setRenderHints(QPainter::HighQualityAntialiasing);

    p.drawPixmap(QPoint(0, 0),
                 m_currentPixmap.scaled(size(),
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation));
}
