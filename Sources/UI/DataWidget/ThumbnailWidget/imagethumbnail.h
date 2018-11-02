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

#ifndef IMAGETHUMBNAIL_H
#define IMAGETHUMBNAIL_H

#include <QWidget>

#include <QPixmap>

#include <QPainter>
#include <QPen>
#include <QBrush>

class ImageThumbnail : public QWidget
{
    Q_OBJECT

public:
    explicit ImageThumbnail(QPixmap *pix, QWidget *parent = nullptr);

    QPixmap *pixmap() const;
    void setPixmap(QPixmap *pixmap);

signals:

public slots:

private:
    QPixmap *m_pixmap;
    QPixmap m_scaledPix;

private:
    void updatePix();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

};

#endif // IMAGETHUMBNAIL_H
