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

#include "audioviewer.h"

AudioViewer::AudioViewer() :
    PluginViewerInterface()
{
}

QWidget *AudioViewer::widget(const QUrl &url, QWidget *parent)
{
    return new AudioWidget(url.toLocalFile(), parent);
}

QStringList AudioViewer::supportedFormats()
{
    return QStringList() << "wav";
}

PluginViewerInterface::PluginInfos AudioViewer::infos()
{
    return PluginInfos("Audio Viewer", "1.0", "Grégoire BOST",
                       "The default plugin to play audio files with MiniClipBoard");
}
