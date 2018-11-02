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

#include "viewer.h"

Viewer::Viewer(const QUrl &url, QWidget *parent) : QWidget(parent)
{
    m_layout = new QGridLayout;

    mw_label = new QLabel(this);

    mw_slider = new QSlider(Qt::Horizontal, this);
    connect(mw_slider, &QSlider::sliderMoved, [=](int pos) {
        m_movie->jumpToFrame(pos);
    });

    m_layout->addWidget(mw_label, 0, 0, 4, 4, Qt::AlignCenter);
    m_layout->addWidget(mw_slider, 4, 0, 1, 4);

    setLayout(m_layout);

    init(url);
}

Viewer::~Viewer()
{
    delete m_movie;
}

void Viewer::init(const QUrl &url)
{
    m_movie = new QMovie(url.toLocalFile());
    mw_slider->setMaximum(m_movie->frameCount());

    connect(m_movie, &QMovie::frameChanged, [=](int frame) {
        mw_label->setPixmap(m_movie->currentPixmap());
        mw_slider->setValue(frame);
    });

    m_movie->start();
}
