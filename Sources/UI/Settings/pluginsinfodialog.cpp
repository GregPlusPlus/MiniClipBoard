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

#include "pluginsinfodialog.h"

PluginsInfoDialog::PluginsInfoDialog(const Plugins::Plugins &plugins, QWidget *parent)
    : m_plugins(plugins), QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Plugins infos"));
    setWindowIcon(QIcon(":/icons/ic_extension_white_18dp"));

    m_layout = new QVBoxLayout;

    mw_header = new QLabel(tr("Detailed informations about plugins"), this);

    mw_infos = new QPlainTextEdit(this);
    mw_infos->setReadOnly(true);
    mw_infos->setWordWrapMode(QTextOption::NoWrap);
    showInfos();

    m_layout->addWidget(mw_header);
    m_layout->addWidget(mw_infos);

    setLayout(m_layout);
}

void PluginsInfoDialog::showInfos()
{
    QString str = QString("%1 plugin(s) loaded.\n\n").arg(m_plugins.count());

    for(Plugins::Plugin plugin : m_plugins) {
        QString infosStr;

        PluginViewerInterface::PluginInfos infos = plugin.interface->infos();

        infosStr = QString("=== %1 === \n"
                          "    Path \t: %2 \n"
                          "    Name \t: %3 \n"
                          "    Version \t: %4 \n"
                          "    Author \t: %5 \n"
                          "    Description : \n"
                          "    %6 \n"
                          "\n\n")
                .arg(QFileInfo(plugin.fileName).fileName())
                .arg(plugin.fileName)
                .arg(infos.name)
                .arg(infos.version)
                .arg(infos.author)
                .arg(infos.description);

        str += infosStr;
    }

    mw_infos->setPlainText(str);
}
