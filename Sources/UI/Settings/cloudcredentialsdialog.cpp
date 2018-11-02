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

#include "cloudcredentialsdialog.h"

CloudCredentialsDialog::CloudCredentialsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle(tr("Cloud credentials"));
    setWindowIcon(QIcon(":/icons/ic_cloud_upload_white_18dp"));
    setMinimumWidth(400);

    m_layout = new QVBoxLayout;

    m_pastebinLayout = new QGridLayout;
    mw_pastebinGroup = new QGroupBox(tr("Pastebin"), this);

    mw_pastebinGroup->setLayout(m_pastebinLayout);

    mw_pastebinApiKeySave = new FlatActionButton(QIcon(":/icons/ic_check_white_18dp"), tr("Save"), this);
    mw_pastebinApiKeySave->setEnabled(false);
    connect(mw_pastebinApiKeySave, &FlatActionButton::clicked, this, &CloudCredentialsDialog::savePastebinKey);

    mw_pastebinApiKey = new LineEdit(this);
    mw_pastebinApiKey->setPlaceholderText(tr("Enter your API key here"));
    connect(mw_pastebinApiKey, &LineEdit::textChanged, [=](const QString &key) {
        if(!Pastebin::pastebinKeySeemsvalid(key)) {
            mw_pastebinApiKey->setBorderColor(QColor("#FF234F"));
            mw_pastebinApiKeySave->setEnabled(false);
            mw_pastebinApiKeySave->setCursor(Qt::ForbiddenCursor);
        } else {
            mw_pastebinApiKey->setBorderColor(QColor("#A8FFA8"));
            mw_pastebinApiKeySave->setEnabled(true);
            mw_pastebinApiKeySave->setCursor(Qt::PointingHandCursor);
        }
    });

    mw_pastebinHelpButton = new QPushButton(tr("How to get an API key ?"), this);
    mw_pastebinHelpButton->setFlat(true);
    mw_pastebinHelpButton->setCursor(Qt::PointingHandCursor);
    connect(mw_pastebinHelpButton, &QPushButton::clicked, [=]() {
        QMessageBox::information(this, tr("How to get an API key ?"),
                                 tr("<h2>How to get an API key ?</h2>"
                                    "<p>"
                                    "In order to get an API key for Pastebin, you must create an account or login at <a style=\"color: #3399ff;\" href=\"https://pastebin.com/login\">https://pastebin.com/login</a><br>"
                                    "Next, go to <a style=\"color: #3399ff;\" href=\"https://pastebin.com/api\">https://pastebin.com/api</a> while logged on, then jump to <i>Your Unique Developer API Key</i> section.<br>"
                                    "Here will be your <i>Developer API Key</i>. Copy this key and paste it in the field."
                                    "</p>"));
    });

    m_pastebinLayout->addWidget(mw_pastebinApiKey,     0, 0, 1, 4);
    m_pastebinLayout->addWidget(mw_pastebinApiKeySave, 0, 4, 1, 1);
    m_pastebinLayout->addWidget(mw_pastebinHelpButton, 1, 0, 1, 5);

    m_layout->addWidget(mw_pastebinGroup);

    setLayout(m_layout);

    init();
}

void CloudCredentialsDialog::savePastebinKey()
{
    CloudUtils::setValue("Pastebin", "pastebin_api_key", mw_pastebinApiKey->text());

    QMessageBox::information(this, tr("Success"), tr("Key successfully saved !<br>"
                                                     "Your key : <strong>%1</strong><br>"
                                                     "Please keep this key private and DO NOT abuse the service.").arg(mw_pastebinApiKey->text()));
}

void CloudCredentialsDialog::init()
{
    mw_pastebinApiKey->setText(CloudUtils::getValue("Pastebin/pastebin_api_key"));
}
