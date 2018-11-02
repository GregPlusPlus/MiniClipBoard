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

#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>

#include <QGridLayout>

#include <QDebug>

class DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadDialog(QWidget *parent = nullptr);

signals:
    void cancelDownload();

public slots:
    void setProgress(qint64 received, qint64 total);
    void setRate(qint64 rate, qint64 remaining);
    void downloadFinished();
    void setMessage(const QString &text);

private:
    QGridLayout  *m_layout;

    QLabel       *mw_message;
    QLabel       *mw_rateTimeLabel;
    QProgressBar *mw_progress;
    QPushButton  *mw_hide;
    QPushButton  *mw_cancel;
};

#endif // DOWNLOADDIALOG_H
