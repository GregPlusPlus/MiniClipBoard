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

#include <QApplication>

#include <QCommandLineParser>

#include <qtwebengineglobal.h>

#include "Core/SettingsManager/settingsmanager.h"
#include "Utils/utils.h"
#include "Utils/mainutils.h"
#include "UI/MainWindow/mainwindow.h"
#include "UI/UtilsUI/utilsui.h"

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QDir::setCurrent(qApp->applicationDirPath());

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("MiniClipBoard");
    QCoreApplication::setApplicationVersion(Utils::appVersion());

    QApplication a(argc, argv);
    QtWebEngine::initialize();

    if(!MainUtils::setAsUniqueProcess(a)) {
        return 0;
    }

    qDebug() << QString("App data path : %1").arg(Utils::appDataPath());

    UtilsUI::applyStyleSheet(":/css/app");

    SettingsManager settingsManager;

    settingsManager.setFilename(Utils::appDataPath() + "settings.ini");
    settingsManager.load();

    MainUtils::translate(&a, settingsManager.lang());

    qDebug() << QObject::tr("OpenSSL build version : '%1'. Please check binaries version if you encounter SSL errors.").arg(QSslSocket::sslLibraryBuildVersionString());

    MainWindow w;
    w.setSettingsManager(&settingsManager);

    if(settingsManager.settings()->firstStart) {
        w.toggleWindow();

        settingsManager.settings()->firstStart = false;
        settingsManager.save();
    }

    return a.exec();
}
