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

#include "downloaddialog.h"

DownloadDialog::DownloadDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::WindowTitleHint | Qt::SubWindow/* | Qt::WindowStaysOnTopHint*/);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("Downloading file..."));

    m_layout = new QGridLayout;
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    mw_message = new QLabel(tr("Downloading file..."), this);
    mw_message->setTextFormat(Qt::RichText);
    mw_message->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mw_message->setOpenExternalLinks(true);

    mw_rateTimeLabel = new QLabel(tr("--- KiB/s - Unknown remaining time"));

    mw_progress = new QProgressBar(this);
    mw_progress->setTextVisible(false);

    mw_hide = new QPushButton(tr("Hide"), this);
    mw_hide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(mw_hide, &QPushButton::clicked, this, &DownloadDialog::close);

    mw_cancel = new QPushButton(tr("Cancel"), this);
    mw_cancel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(mw_cancel, &QPushButton::clicked, this, &DownloadDialog::cancelDownload);

    m_layout->addWidget(mw_message,         0, 0, 1, 1);
    m_layout->addWidget(mw_progress,        1, 0, 1, 4);
    m_layout->addWidget(mw_rateTimeLabel,   2, 0, 1, 1);
    m_layout->addWidget(mw_hide,            2, 2, 1, 1);
    m_layout->addWidget(mw_cancel,          2, 3, 1, 1);

    setLayout(m_layout);
}

void DownloadDialog::setProgress(qint64 received, qint64 total)
{
    mw_progress->setMaximum(total);
    mw_progress->setValue(received);
}

void DownloadDialog::setRate(qint64 rate, qint64 remaining)
{
    if(rate == 0 || remaining == 0) {
        mw_rateTimeLabel->setText(tr("--- KiB/s - Unknown remaining time"));

        return;
    }

    qint64 time = remaining / rate;
    QString str_time;

    if(time >= 86400) {
        str_time = tr("%1 Days %2 Hours").arg(time / 86400).arg((time % 86400) / 3600);
    } else if(time >= 3600) {
        str_time = tr("%1 Hours %2 Minutes").arg(time / 3600).arg((time % 3600) / 60);
    } else if(time >= 60) {
        str_time = tr("%1 Minutes %2 Seconds").arg(time / 60).arg(time % 60);
    } else {
        str_time = tr("%1 Seconds").arg(time);
    }

    mw_rateTimeLabel->setText(tr("%1 KiB/s - Remaining time : %2")
                              .arg(rate / 1024)
                              .arg(str_time));
}

void DownloadDialog::downloadFinished()
{
    deleteLater();
}

void DownloadDialog::setMessage(const QString &text)
{
    mw_message->setText(text);
}
