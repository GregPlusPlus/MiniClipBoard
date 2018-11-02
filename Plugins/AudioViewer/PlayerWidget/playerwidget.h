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

#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>

#include <QMessageBox>

#include <QHBoxLayout>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QMediaPlayer>

#include <QDateTime>

#include <QDebug>

#include "flatactionbutton.h"
#include "popupvolume.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = nullptr, const QString &fileName = QString());
    ~PlayerWidget();

signals:
    void error(QMediaPlayer::Error error, const QString &text);

public slots:
    void setFileName(const QString &fileName);
    void load();
    void togglePlay();
    void _error(QMediaPlayer::Error code);

private:
    QHBoxLayout         *m_layout;
    FlatActionButton    *mw_playButton;
    QLabel              *mw_elapsed;
    QSlider             *mw_slider;
    QLabel              *mw_total;
    FlatActionButton    *mw_volumeButton;

    PopupVolume         *mw_popupVolume;

    QString m_fileName;

    QMediaPlayer *m_player;

private:
    void init();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PLAYERWIDGET_H
