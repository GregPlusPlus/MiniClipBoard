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

#include "downloaddialog.h"

DownloadDialog::DownloadDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Downloading file..."));

    m_layout = new QGridLayout;

    mw_message = new QLabel(tr("Downloading file..."), this);
    mw_message->setTextFormat(Qt::RichText);
    mw_message->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mw_message->setOpenExternalLinks(true);

    mw_progress = new QProgressBar(this);
    mw_progress->setTextVisible(false);

    m_layout->addWidget(mw_message, 0, 0, 1, 1);
    m_layout->addWidget(mw_progress, 1, 0, 1, 1);

    setLayout(m_layout);
}

void DownloadDialog::progress(qint64 received, qint64 total)
{
    mw_progress->setMaximum(total);
    mw_progress->setValue(received);
}

void DownloadDialog::downloadFinished()
{
    deleteLater();
}

void DownloadDialog::setMessage(const QString &text)
{
    mw_message->setText(text);
}
