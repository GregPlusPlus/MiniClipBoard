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

#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent, const QString &fileName) : QWidget(parent)
{
    setFileName(fileName);

    setMaximumHeight(40);

    init();

    m_layout = new QHBoxLayout;

    mw_playButton = new FlatActionButton(QIcon(":/icons/ic_play_arrow_white_24dp"), tr("Play/Pause"), this);
    connect(mw_playButton, &FlatActionButton::clicked, this, &PlayerWidget::togglePlay);

    mw_elapsed = new QLabel(tr("--"), this);

    mw_slider = new QSlider(Qt::Horizontal, this);
    connect(mw_slider, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);

    mw_total = new QLabel(tr("--"), this);

    mw_volumeButton = new FlatActionButton(QIcon(":/icons/ic_volume_up_white_24dp"), tr("Adjust volume"), this);

    mw_popupVolume = new PopupVolume;
    mw_popupVolume->setAnchorWidget(mw_volumeButton);
    connect(mw_volumeButton, &FlatActionButton::clicked, mw_popupVolume, &InfosPopup::trigger);
    connect(mw_popupVolume, &PopupVolume::volumeChanged, [=](int volume) {
        m_player->setVolume(volume);

        if(volume < 30 && volume >= 0) {
            mw_volumeButton->setIcon(QIcon(":/icons/ic_volume_mute_white_24dp"));
        } else if(volume < 60 && volume >= 30) {
            mw_volumeButton->setIcon(QIcon(":/icons/ic_volume_down_white_24dp"));
        } else if(volume <= 100 && volume >= 60) {
            mw_volumeButton->setIcon(QIcon(":/icons/ic_volume_up_white_24dp"));
        }
    });
    mw_popupVolume->setVolume(50);

    m_layout->addWidget(mw_playButton, Qt::AlignLeft);
    m_layout->addWidget(mw_elapsed);
    m_layout->addWidget(mw_slider);
    m_layout->addWidget(mw_total);
    m_layout->addWidget(mw_volumeButton);

    setLayout(m_layout);
}

PlayerWidget::~PlayerWidget()
{
    mw_popupVolume->cleanDestroy();
}

void PlayerWidget::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

void PlayerWidget::load()
{
    m_player->setMedia(QUrl::fromLocalFile(m_fileName));
    m_player->setVolume(mw_popupVolume->volume());
}

void PlayerWidget::togglePlay()
{
    if(m_player->state() == QMediaPlayer::PlayingState) {
        mw_playButton->setIcon(QIcon(":/icons/ic_play_arrow_white_24dp"));
        m_player->pause();
    } else {
        mw_playButton->setIcon(QIcon(":/icons/ic_pause_white_24dp"));
        m_player->play();
    }
}

void PlayerWidget::_error(QMediaPlayer::Error code)
{
    emit error(code, m_player->errorString());

    mw_playButton->setIcon(QIcon(":/icons/ic_play_arrow_white_24dp"));
    mw_elapsed->setText("--");
    mw_total->setText("--");
}

void PlayerWidget::init()
{
    m_player = new QMediaPlayer(this);

    connect(m_player, &QMediaPlayer::positionChanged, [=](qint64 position) {
        mw_slider->setValue(position);
        mw_elapsed->setText(QTime(0, 0, 0, 0).addMSecs(position).toString("mm:ss"));
    });
    connect(m_player, &QMediaPlayer::durationChanged, [=](qint64 duration) {
        mw_slider->setMaximum(duration);
        mw_total->setText(QTime(0, 0, 0, 0).addMSecs(duration).toString("mm:ss"));
        mw_elapsed->setText(QTime(0, 0, 0, 0).addMSecs(m_player->position()).toString("mm:ss"));
    });
    connect(m_player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(_error(QMediaPlayer::Error)));
}

void PlayerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHints(QPainter::HighQualityAntialiasing);

    QLinearGradient grad(QPoint(0, 0), QPoint(0, height()));
    grad.setColorAt(0, QColor("#323D47"));
    grad.setColorAt(1, QColor("#242C33"));

    p.setBrush(grad);
    p.setPen(QPen(QColor("#19232D"), 1.2));

    p.drawRoundedRect(rect(), 5, 5);
}
