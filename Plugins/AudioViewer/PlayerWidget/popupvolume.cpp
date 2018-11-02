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

#include "popupvolume.h"

PopupVolume::PopupVolume() : InfosPopup(Side_Top)
{
    setFixedSize(30, 130);

    m_layout = new QVBoxLayout;
    m_layout->setMargin(3);

    mw_slider = new QSlider(Qt::Vertical, this);
    mw_slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mw_slider->setMaximum(100);
    connect(mw_slider, &QSlider::valueChanged, this, &PopupVolume::volumeChanged);
    connect(mw_slider, &QSlider::valueChanged, [=](int value) {
        mw_label->setText(QString::number(value));
    });

    mw_label = new QLabel(QString::number(mw_slider->value()), this);
    mw_label->setAlignment(Qt::AlignCenter);

    m_layout->addWidget(mw_slider);
    m_layout->addWidget(mw_label);

    setLayout(m_layout);
}

int PopupVolume::volume()
{
    return mw_slider->value();
}

void PopupVolume::setVolume(int volume)
{
    mw_slider->setValue(volume);
}
