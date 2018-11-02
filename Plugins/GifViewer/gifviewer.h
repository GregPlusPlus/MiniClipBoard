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

#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include <QGenericPlugin>

#include "../../Sources/Plugins/interface.h"

#include "viewer.h"


class GifViewer : public QObject, PluginViewerInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginViewerInterface_iid FILE "GifViewer.json")
    Q_INTERFACES(PluginViewerInterface)

public:
    GifViewer();
    QWidget *widget(const QUrl &url, QWidget *parent) override;
    QStringList supportedFormats() override;
    PluginInfos infos() override;
};

#endif // GENERICPLUGIN_H
