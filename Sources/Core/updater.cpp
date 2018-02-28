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

#include "updater.h"

Updater::Updater() : QObject()
{
    m_p_reply = nullptr;
}

void Updater::checkForUpdates()
{
    m_p_reply = m_manager.get(QNetworkRequest(QUrl(Updater::versionsURL())));

    connect(m_p_reply, SIGNAL(finished()), this, SLOT(downloadCheckFinished()));
    connect(m_p_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    connect(m_p_reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), [=](QNetworkReply::NetworkError code) {
        Q_UNUSED(code)
        emit error(m_p_reply->errorString());
    });
}

void Updater::downloadNewVersion()
{
    m_p_reply = m_manager.get(QNetworkRequest(QUrl(m_last.installerURL)));

    disconnect(m_p_reply, SIGNAL(finished()), this, SLOT(downloadCheckFinished()));
    connect(m_p_reply, SIGNAL(finished()), this, SLOT(downloadInstallerFinished()));
    connect(m_p_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    connect(m_p_reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), [=](QNetworkReply::NetworkError code) {
        Q_UNUSED(code)
        emit error(m_p_reply->errorString());
    });
}

QString Updater::versionsURL()
{
    //return "http://localhost/MiniClipBohard/versions.xml";
    return "https://raw.githubusercontent.com/GregPlusPlus/MiniClipBoard/master/Git/versions.xml";
}

void Updater::downloadCheckFinished()
{
    m_p_reply->deleteLater();

    extractVersions(m_p_reply->readAll());

    m_last = extractLastVersion();

    emit finishedCheck(m_last.version, m_last.changelog, checkIfAppIsLastVersion(m_last));
}

void Updater::downloadInstallerFinished()
{
    m_p_reply->deleteLater();

    m_dataInstaller = m_p_reply->readAll();

    emit downloadFinished();
}

void Updater::cancel()
{
    if(!m_p_reply) {
        return;
    }

    disconnect(m_p_reply, SIGNAL(finished()), this, SLOT(downloadInstallerFinished()));
    disconnect(m_p_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
}

Updater::Version Updater::getLastVersion() const
{
    return m_last;
}

QByteArray Updater::getDataInstaller() const
{
    return m_dataInstaller;
}

void Updater::extractVersions(QString xml)
{
    QDomDocument dom("versions");

    if(dom.setContent(xml)) {
        QDomElement dom_element = dom.documentElement();
        QDomNode node = dom_element.firstChild();

        while(!node.isNull()) {
            QDomElement element = node.toElement();
            if(!element.isNull()) {
                if(element.attribute("os", "") == Utils::buildOS()) {
                    m_versions.append(Version(element.attribute("installer", ""), element.attribute("version", "UNKNOWN"), tr("Released on %1.\n%2").arg(element.attribute("releaseDate", "--/--/--")).arg(element.text())));
                }
            }

            node = node.nextSibling();
        }
    }
}

Updater::Version Updater::extractLastVersion()
{
    Version lastVersion;

    for(int i = 0; i < m_versions.count(); i++) {
        QStringList version_str = m_versions.at(i).version.split('.', QString::SkipEmptyParts);

        int version_int = 0;
        for(int j = version_str.count() - 1; j >= 0; j--) {
            version_int += (QString(version_str.at(j)).toInt() * pow(10, (version_str.count() - j) - 1));
        }

        m_versions[i].versionInt = version_int;
    }

    for(int i = 0; i < m_versions.count(); i++) {
        if(m_versions.at(i).versionInt >= lastVersion.versionInt) {
            lastVersion = m_versions.at(i);
        }
    }

    return lastVersion;
}

bool Updater::checkIfAppIsLastVersion(const Version &version)
{
    QStringList version_str = Utils::appVersion().split('.', QString::SkipEmptyParts);

    int version_int = 0;
    for(int j = version_str.count() - 1; j >= 0; j--) {
        version_int += (QString(version_str.at(j)).toInt() * pow(10, (version_str.count() - j) - 1));
    }

    return (version_int >= version.versionInt);
}
