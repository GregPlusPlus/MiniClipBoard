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

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtWidgets/QWidget>

#include <QUrl>
#include <QStringList>

class PluginViewerInterface
{
public:
    struct PluginInfos
    {
        PluginInfos() {}
        PluginInfos(QString _name, QString _version, QString _author, QString _description) :
            name(_name), version(_version), author(_author), description(_description) {}

        QString name;
        QString version;
        QString author;
        QString description;
    };

public:
    virtual ~PluginViewerInterface() {}
    virtual QWidget *widget(const QUrl &url, QWidget *parent) = 0;
    virtual QStringList supportedFormats() = 0;
    virtual PluginInfos infos() = 0;
};

#define PluginViewerInterface_iid "MiniClipBoard.PluginViewerInterface"

Q_DECLARE_INTERFACE(PluginViewerInterface, PluginViewerInterface_iid)

#endif // INTERFACE_H
