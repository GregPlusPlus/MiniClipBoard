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

#ifndef UPDATERUTILS_H
#define UPDATERUTILS_H

#include <QObject>

#include <QMessageBox>

#include <QProcess>

#include "../updater.h"
#include "../../UI/DownloadDialog/downloaddialog.h"
#include "../../Utils/utils.h"

class UpdaterUtils : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterUtils(QObject *parent = nullptr);

signals:
    void progress(int current, int max, bool drawprogress);

public slots:
    void checkForUpdates();
    void updaterFinishedCheck(QString version, QString changelog, bool isAppLastVersion);
    void updaterDownloadFinished();

private:
    Updater m_updater;

    QString m_updaterPath;
};

#endif // UPDATERUTILS_H
