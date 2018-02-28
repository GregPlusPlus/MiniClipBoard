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

#include "updaterutils.h"

UpdaterUtils::UpdaterUtils(QObject *parent) : QObject(parent)
{

}

void UpdaterUtils::checkForUpdates()
{
    disconnect(&m_updater, SIGNAL(finishedCheck(QString,QString,bool)), this, SLOT(updaterFinishedCheck(QString,QString,bool)));
    connect(&m_updater, SIGNAL(finishedCheck(QString,QString,bool)), this, SLOT(updaterFinishedCheck(QString,QString,bool)));
    m_updater.checkForUpdates();
}

void UpdaterUtils::updaterFinishedCheck(QString version, QString changelog, bool isAppLastVersion)
{
    if(isAppLastVersion) {
        return;
    }

    QString fileSuffix = Utils::executableFileSuffix();

    m_updaterPath = QString("MiniClipBoard_update%1").arg(fileSuffix);

    QMessageBox box(QMessageBox::Question,
                    tr("Updates available"),
                    tr("A new version of MiniClipBoard is available.<br>New version : <i>%1</i> | Current version : <i>%2</i><br>Do you want to download and install it?").arg(version).arg(Utils::appVersion()),
                    QMessageBox::Yes | QMessageBox::No);
    box.setDetailedText(changelog);
    box.exec();

    if(box.standardButton(box.clickedButton()) == QMessageBox::Yes) {
        DownloadDialog *dial = new DownloadDialog();
        dial->setMessage(tr("Connecting to <a href=\"%1\">%2</a> ...").arg(m_updater.getLastVersion().installerURL).arg(m_updater.getLastVersion().installerURL));

        connect(dial, &DownloadDialog::cancelDownload, [=]() {
            m_updater.cancel();
            dial->close();
            emit progress(0, 0, false);
            QMessageBox::information(nullptr, tr("Download canceled"), tr("Download canceled !"));
        });
        connect(&m_updater, &Updater::downloadFinished, [=]() {
            dial->setMessage(tr("Writing file to disk..."));

            QFile lastversion(m_updaterPath);

            if(lastversion.open(QIODevice::WriteOnly)) {
                lastversion.write(m_updater.getDataInstaller());
                lastversion.close();

                dial->setMessage(tr("Ready to install..."));

                updaterDownloadFinished();

                dial->close();
            } else {
                QMessageBox::warning(nullptr, tr("Failed to update MiniClipBoard"), tr("Unable to write file to disk.<br><i>%1</i>").arg(lastversion.errorString()));
            }
        });
        //connect(&m_updater, SIGNAL(finishedDownload()), this, SLOT(updaterDownloadFinished()));
        connect(&m_updater, &Updater::progress, [=](qint64 current, qint64 max) {
            dial->setProgress(current, max);
            dial->setMessage(tr("Downloading file from <a href=\"%1\">%2</a> ...").arg(m_updater.getLastVersion().installerURL).arg(m_updater.getLastVersion().installerURL));

            emit progress(current, max, true);
        });
        connect(&m_updater, &Updater::error, [=](QString error) {
            emit progress(0, 0, false);

            QMessageBox::warning(nullptr, tr("Updater error !"), tr("An error occured when downloading file : <br><i>%1</i>").arg(error));
        });

        m_updater.downloadNewVersion();
        dial->show();
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
