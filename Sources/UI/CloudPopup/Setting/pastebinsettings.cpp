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

#include "pastebinsettings.h"

PastebinSettings::PastebinSettings(QWidget *parent) : QWidget(parent)
{
    m_layout = new QGridLayout;

    mw_nameInput = new LineEdit(this);
    mw_nameInput->setPlaceholderText(tr("Paste name"));
    mw_nameInput->setFixedHeight(35);
    connect(mw_nameInput, &LineEdit::returnPressed, this, &PastebinSettings::upload);

    mw_cancelButton = new FlatActionButton(QIcon(":/icons/ic_clear_white_18dp"), tr("Cancel"), this);
    connect(mw_cancelButton, &FlatActionButton::clicked, [=]() {
        if(mw_optionsGroup->isVisible()) {
            toggleOptions();
        }

        emit cancel();
    });

    mw_optionsButton = new FlatActionButton(QIcon(":/ui-images/scroll_bottom"), tr("Options"), this);
    connect(mw_optionsButton, &FlatActionButton::clicked, this, &PastebinSettings::toggleOptions);

    mw_sendButton = new FlatActionButton(QIcon(":/icons/ic_send_white_18dp"), tr("Send"), this);
    mw_sendButton->setFocus();
    connect(mw_sendButton, &FlatActionButton::clicked, this, &PastebinSettings::upload);

    m_optionsLayout = new QFormLayout;

    mw_optionsGroup = new QGroupBox(tr("Options..."), this);
    mw_optionsGroup->setLayout(m_optionsLayout);
    mw_optionsGroup->hide();

    mw_expire = new QComboBox(this);

    mw_private = new QComboBox(this);

    m_optionsLayout->addRow(tr("Expire  : "), mw_expire);
    m_optionsLayout->addRow(tr("Private : "), mw_private);

    initOptions();

    mw_infosKeyButton = new QPushButton(tr("Your key is not valid. Details..."), this);
    mw_infosKeyButton->setFlat(true);
    mw_infosKeyButton->setCursor(Qt::PointingHandCursor);
    connect(mw_infosKeyButton, &QPushButton::clicked, [=]() {
        QMessageBox::information(this, tr("About Pastebin API key..."), tr("To upload data to Pastebin you need an API key.<br>"
                                                                           "Go to \"Cloud settings\" → \"Cloud credentials\" to enter your key and get more informations."));
    });

    mw_reloadKeyButton = new QPushButton(QIcon(":/icons/ic_refresh_white_18dp"), tr("Reload key"), this);
    mw_reloadKeyButton->setFlat(true);
    mw_reloadKeyButton->setCursor(Qt::PointingHandCursor);
    connect(mw_reloadKeyButton, &QPushButton::clicked, this, &PastebinSettings::checkKey);

    m_layout->addWidget(mw_cancelButton   , 0, 0, 1, 1);
    m_layout->addWidget(mw_nameInput      , 0, 1, 1, 4);
    m_layout->addWidget(mw_optionsButton  , 0, 5, 1, 1);
    m_layout->addWidget(mw_sendButton     , 0, 6, 1, 1);
    m_layout->addWidget(mw_optionsGroup   , 1, 0, 1, 7);
    m_layout->addWidget(mw_infosKeyButton , 2, 0, 1, 6);
    m_layout->addWidget(mw_reloadKeyButton, 2, 6, 1, 1);

    setLayout(m_layout);
}

void PastebinSettings::upload()
{
    CloudTypes::CloudData data;

    data.settings["name"] = mw_nameInput->text();
    applyOptions(data);

    data.platform = CloudTypes::Cloud_Platform_Pastebin;

    if(mw_optionsGroup->isVisible()) {
        toggleOptions();
    }

    emit send(data);
}

void PastebinSettings::checkKey()
{
    bool valid = Pastebin::pastebinKeySeemsvalid(CloudUtils::getValue("Pastebin/pastebin_api_key"));

    mw_nameInput->setEnabled(valid);
    mw_sendButton->setEnabled(valid);
    mw_infosKeyButton->setVisible(!valid);
    mw_reloadKeyButton->setVisible(!valid);
}

void PastebinSettings::initOptions()
{
    QStringList expireOptions;
    expireOptions << tr("Never")
                  << tr("10 Minutes")
                  << tr("1 Hour")
                  << tr("1 Day")
                  << tr("1 Week")
                  << tr("2 Weeks")
                  << tr("1 Month")
                  << tr("6 Months")
                  << tr("1 Year");
    mw_expire->addItems(expireOptions);
    mw_expire->setCurrentIndex(0);

    QStringList privateOptions;
    privateOptions << tr("Public")
                   << tr("Unlisted");
    mw_private->addItems(privateOptions);
    mw_private->setCurrentIndex(1);
}

void PastebinSettings::toggleOptions()
{
    mw_optionsGroup->setVisible(!mw_optionsGroup->isVisible());
    if(mw_optionsGroup->isVisible()) {
        mw_optionsButton->setIcon(QIcon(":/ui-images/scroll_top"));
    } else {
        mw_optionsButton->setIcon(QIcon(":/ui-images/scroll_bottom"));
    }
}

void PastebinSettings::applyOptions(CloudTypes::CloudData &data)
{
    QString expireStr;

    switch (mw_expire->currentIndex()) {
    case 0:
        expireStr = "N";
        break;
    case 1:
        expireStr = "10M";
        break;
    case 2:
        expireStr = "1H";
        break;
    case 3:
        expireStr = "1D";
        break;
    case 4:
        expireStr = "1W";
        break;
    case 5:
        expireStr = "2W";
        break;
    case 6:
        expireStr = "1M";
        break;
    case 7:
        expireStr = "6M";
        break;
    case 8:
        expireStr = "1Y";
        break;
    default:
        expireStr = "N";
        break;
    }

    data.settings["expire"] = expireStr;

    QString privateStr;

    switch (mw_private->currentIndex()) {
    case 0:
        privateStr = "0";
        break;
    case 1:
        privateStr = "1";
        break;
    default:
        privateStr = "0";
        break;
    }

    data.settings["private"] = privateStr;
}
