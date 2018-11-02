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

#include "audiowidget.h"

AudioWidget::AudioWidget(const QString &fileName, QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;

    mw_player = new PlayerWidget(parent, fileName);
    mw_player->load();
    connect(mw_player, &PlayerWidget::error, [=](QMediaPlayer::Error error, const QString &text) {
        QMessageBox::warning(this, tr("Unable to play file"), tr("An error occured :<br>"
                                                                 "<i>%1</i><br>"
                                                                 "Code : <strong>%2</strong>")
                             .arg((text.isEmpty())?"Unknown error":text)
                             .arg(error));
    });

    m_layout->addWidget(mw_player);

    setLayout(m_layout);
}
