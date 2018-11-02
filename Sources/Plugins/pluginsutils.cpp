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

#include "pluginsutils.h"

Plugins::Plugins PluginsUtils::loadPlugins()
{
    Plugins::Plugins plugins;

    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    for(QString fileName : pluginsDir.entryList(QDir::Files)) {
        if(QLibrary::isLibrary(fileName)) {
            qDebug() << QObject::tr("Trying to load %1").arg(fileName);

            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();

            qDebug() << pluginLoader.errorString();

            if (plugin) {
                PluginViewerInterface *pluginInterface = qobject_cast<PluginViewerInterface*>(plugin);

                if(pluginInterface) {
                    qDebug() << QObject::tr("%1 loaded.").arg(fileName);

                    plugins.append(Plugins::Plugin(pluginInterface, fileName));
                }
            }
        }
    }

    qDebug() << QObject::tr("%1 plugin(s) loaded.").arg(plugins.count());

    return plugins;
}
