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

#include "updaterutils.h"

UpdaterUtils::UpdaterUtils(QObject *parent) : QObject(parent)
{
    mw_downloadDialog = new DownloadDialog;
    mw_downloadDialog->hide();

    connect(&m_updater, &Updater::error, [=](const QString &error, QNetworkReply::NetworkError code) {;
        emit progress(0, 0, false);

        if(code != QNetworkReply::HostNotFoundError) {
            QMessageBox::warning(nullptr, tr("Updater error !"), tr("An error occured when downloading file : <br><i>%1</i>")
                                 .arg(error));
        }
    });
    connect(&m_updater, &Updater::finishedCheck, this, &UpdaterUtils::updaterFinishedCheck);
    connect(mw_downloadDialog, &DownloadDialog::cancelDownload, [=]() {
        m_updater.cancel();
        mw_downloadDialog->close();
        emit progress(0, 0, false);
        QMessageBox::information(nullptr, tr("Download canceled"), tr("Download canceled !"));
    });
    connect(&m_updater, &Updater::downloadFinished, [=]() {
        mw_downloadDialog->setMessage(tr("Writing file to disk..."));

        QFile lastversion(m_updaterPath);

        if(lastversion.open(QIODevice::WriteOnly)) {
            lastversion.write(m_updater.getDataInstaller());
            lastversion.close();

            mw_downloadDialog->setMessage(tr("Ready to install..."));

            updaterDownloadFinished();

            mw_downloadDialog->close();
        } else {
            QMessageBox::warning(nullptr, tr("Failed to update MiniClipBoard"), tr("Unable to write file to disk.<br><i>%1</i>").arg(lastversion.errorString()));
        }
    });
    connect(&m_updater, &Updater::progress, [=](qint64 current, qint64 max) {
        mw_downloadDialog->setProgress(current, max);

        qint64 elapsed = m_timer.elapsed() / 1000;
        elapsed = ((elapsed == 0) ? 1000 : elapsed);
        qint64 rate = (current - m_lastProgress) / (elapsed);

        mw_downloadDialog->setMessage(tr("Downloading file from <a style=\"color: #93CEFF;\" href=\"%1\">%2</a> ...")
                                      .arg(m_updater.getLastVersion().installerURL)
                                      .arg(m_updater.getLastVersion().installerURL));

        mw_downloadDialog->setRate(rate, max - current);

        emit progress(current, max, true);
    });
}

void UpdaterUtils::checkForUpdates(Updater::Mode mode)
{
    m_updater.checkForUpdates(mode);
}

void UpdaterUtils::updaterFinishedCheck(QString version, QString changelog, bool isAppLastVersion)
{
    if(isAppLastVersion) {
        if(m_updater.getMode() == Updater::Mode_Manual) {
            QMessageBox::information(nullptr, tr("Updates"), tr("MiniClipBoard is up-to-date !<br>Current version : %1").arg(Utils::appVersion()), QMessageBox::Ok);
        }

        return;
    }

    m_updaterPath = m_dir.absolutePath() + QString("/MiniClipBoard_update%1").arg(Utils::executableFileSuffix());

    QMessageBox box(QMessageBox::Question,
                    tr("Updates available"),
                    tr("A new version of MiniClipBoard is available.<br>New version : <i>%1</i> | Current version : <i>%2</i><br>Do you want to download and install it?").arg(version).arg(Utils::appVersion()),
                    QMessageBox::Yes | QMessageBox::No);
    box.setDetailedText(changelog);
    box.exec();

    if(box.standardButton(box.clickedButton()) == QMessageBox::Yes) {
        mw_downloadDialog->show();
        mw_downloadDialog->setMessage(tr("Connecting to <a style=\"color: #93CEFF;\" href=\"%1\">%2</a> ...").arg(m_updater.getLastVersion().installerURL).arg(m_updater.getLastVersion().installerURL));

        m_lastProgress = 0;
        m_timer.start();


        m_updater.downloadNewVersion();
    }
}

void UpdaterUtils::updaterDownloadFinished()
{
    emit progress(0, 0, false);

    if(QMessageBox::question(nullptr, tr("Download completed!"),
                             tr("MiniClipBoard must be closed to complete the installation.<br>"
                                "Do you want to close MiniClipBoard ?<br>If not, the installation will be canceled."),
                             QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Yes) {

        QProcess::startDetached(m_updaterPath);

        qApp->exit();
    } else {
        QMessageBox::information(nullptr, tr("Installation canceled"), tr("Installation canceled !"));
    }
}

QDir UpdaterUtils::dir() const
{
    return m_dir;
}

void UpdaterUtils::setDir(const QDir &dir)
{
    m_dir = dir;
}
