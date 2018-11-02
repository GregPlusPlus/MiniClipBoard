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

#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QLabel>
#include <QSlider>

#include <QGridLayout>

#include <QMovie>

#include <QUrl>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(const QUrl &url, QWidget *parent = nullptr);
    ~Viewer();

signals:

public slots:

private:
    QGridLayout *m_layout;
    QLabel      *mw_label;
    QSlider     *mw_slider;

    QMovie *m_movie;

private:
    void init(const QUrl &url);
};

#endif // VIEWER_H
