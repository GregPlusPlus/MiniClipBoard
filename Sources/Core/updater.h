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

#ifndef UPDATER_H
#define UPDATER_H

#include <QApplication>
#include <QString>

#include <QList>
#include <QStringList>

#include <QUrl>

#include <QtNetwork>

#include <QtXml>

#include <QDebug>

#include <cmath>

#include "../Utils/utils.h"

class Updater : public QObject
{
    Q_OBJECT

public :
    struct Version
    {
        Version(QString _installerURL = QString(), QString _version = QString(), QString _changelog = QString(), int _versionInt = -1) : installerURL(_installerURL), version(_version), changelog(_changelog), versionInt(_versionInt){}
        QString installerURL;
        QString version;
        QString changelog;
        int versionInt = -1;
    };

public:
    Updater();
    void checkForUpdates();
    void downloadNewVersion();

    static QString versionsURL();

    QByteArray getDataInstaller() const;

    Version getLastVersion() const;

signals:
    void finishedCheck(QString version, QString changelog, bool isAppLastVersion);
    void downloadFinished();
    void progress(qint64 received, qint64 total);
    void error(QString error);

public slots:
    void downloadCheckFinished();
    void downloadInstallerFinished();

private:
    QNetworkReply *m_reply;
    QNetworkAccessManager m_manager;

    QList<Version> m_versions;
    QByteArray m_dataInstaller;

    Version m_last;

private:
    void extractVersions(QString xml);
    Version extractLastVersion();
    bool checkIfAppIsLastVersion(const Version &version);
};

#endif // UPDATER_H
