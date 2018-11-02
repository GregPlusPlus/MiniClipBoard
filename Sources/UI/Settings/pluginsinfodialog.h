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

#ifndef PLUGINSINFODIALOG_H
#define PLUGINSINFODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPlainTextEdit>

#include <QVBoxLayout>

#include <QIcon>

#include <QFileInfo>

#include "../../plugins/plugins.h"

class PluginsInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PluginsInfoDialog(const Plugins::Plugins &plugins, QWidget *parent = nullptr);

signals:

public slots:

private:
    QVBoxLayout     *m_layout;
    QLabel          *mw_header;
    QPlainTextEdit  *mw_infos;

    Plugins::Plugins m_plugins;

private:
    void showInfos();
};

#endif // PLUGINSINFODIALOG_H
