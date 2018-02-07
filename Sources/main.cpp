/************************ LICENSING & COPYRIGHT ***********************
Copyright © 2017 Grégoire BOST

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

#include "mainwindow.h"
#include "Utils/utils.h"
#include "UI/UtilsUI/utilsui.h"

#include <QApplication>
#include <QTranslator>

#include "Core/settingsmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(qApp->applicationDirPath());

    UtilsUI::applyStyleSheet(":/css/app");

    SettingsManager manager;
    manager.setFilename("settings.ini");
    manager.load();

    QTranslator translator;
    translator.load("Translations/MiniClipBoard_" + manager.lang());
    a.installTranslator(&translator);

    MainWindow w;
    w.setSettingsManager(&manager);

    return a.exec();
}
