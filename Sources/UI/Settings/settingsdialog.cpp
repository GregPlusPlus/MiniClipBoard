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

#include "settingsdialog.h"

SettingsDialog::SettingsDialog(SettingsManager *manager, QWidget *parent) : QDialog(parent), m_manager(manager)
{
    setWindowIcon(QIcon(":/icons/ic_help_outline_white_18dp"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_mainLayout->setMargin(0);

    m_layout = new QVBoxLayout;
    m_layout->setMargin(10);

    mw_reinterpretGroupBox = new QGroupBox(tr("Reinterpret data"), this);
    m_reinterpretLayout = new QVBoxLayout;
    mw_reinterpretGroupBox->setLayout(m_reinterpretLayout);

    mw_reinterpretUrl = new QCheckBox(tr("Reinterpret text as URL"), this);
    mw_reinterpretColor = new QCheckBox(tr("Reinterpret text as color"), this);

    m_reinterpretLayout->addWidget(mw_reinterpretUrl);
    m_reinterpretLayout->addWidget(mw_reinterpretColor);

    mw_notify = new QCheckBox(tr("Notify each time there is a new copy"), this);

    mw_showThumbnails = new QCheckBox(tr("Show thumbnails"), this);

    mw_alwaysOnTop = new QCheckBox(tr("Window always on top"), this);

    mw_langGroupBox = new QGroupBox(tr("Language"), this);
    m_langLayout = new QHBoxLayout;
    mw_langGroupBox->setLayout(m_langLayout);

    mw_lang = new QComboBox(this);
    mw_lang->addItem("AUTO");
    mw_lang->addItem("en");

    mw_infoLang = new QPushButton(QIcon(":/icons/ic_info_white_18dp"), QString(), this);
    mw_infoLang->setFixedSize(20, 20);
    mw_infoLang->setCursor(Qt::PointingHandCursor);
    mw_infoLang->setFlat(true);
    mw_infoLang->setToolTip(tr("About languages..."));
    connect(mw_infoLang, &QPushButton::clicked, [=]() {
        QMessageBox::information(this, tr("About languages..."), tr("By choosing \"AUTO\" language, the system language will be used if available.<br>"
                                                                    "English is the default language and can't be removed.<br>"
                                                                    "Once you set the right language, you will need to restart the app."));
    });

    m_langLayout->addWidget(mw_lang);
    m_langLayout->addWidget(mw_infoLang);

    mw_legalInfosGroup = new QGroupBox(tr("Legal informations"), this);
    m_legalInfoslayout = new QVBoxLayout;
    mw_legalInfosGroup->setLayout(m_legalInfoslayout);

    mw_aboutButton = new QPushButton(tr("About MiniClipBoard..."), this);
    connect(mw_aboutButton, &QPushButton::clicked, [=]() {
        AboutDialog dialog;
        dialog.exec();
    });

    mw_creditsButton = new QPushButton(tr("Credits"), this);
    connect(mw_creditsButton, &QPushButton::clicked, [=]() {
        CreditsDialog dialog;
        dialog.exec();
    });

    m_legalInfoslayout->addWidget(mw_aboutButton);
    m_legalInfoslayout->addWidget(mw_creditsButton);

    m_layout->addWidget(mw_reinterpretGroupBox);
    m_layout->addWidget(mw_notify);
    m_layout->addWidget(mw_showThumbnails);
    m_layout->addWidget(mw_alwaysOnTop);
    m_layout->addWidget(mw_langGroupBox);
    m_layout->addWidget(UtilsUI::createSeparator());
    m_layout->addWidget(mw_legalInfosGroup);

    mw_statusBar = new QStatusBar(this);
    mw_statusBar->setSizeGripEnabled(false);
    showAppInfos();

    m_mainLayout->addLayout(m_layout);
    m_mainLayout->addWidget(mw_statusBar);

    setLayout(m_mainLayout);

    initUISettings();

    connect(mw_reinterpretUrl, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_reinterpretColor, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_notify, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_showThumbnails, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_alwaysOnTop, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_lang, SIGNAL(activated(QString)), this, SLOT(settingsUIChanged()));
}

void SettingsDialog::initUISettings()
{
    if((m_manager->settings()->reinterpret & Core::ReinterpretData_TextToUrl) != 0) {
        mw_reinterpretUrl->setChecked(true);
    }

    if((m_manager->settings()->reinterpret & Core::ReinterpretData_TextToColor) != 0) {
        mw_reinterpretColor->setChecked(true);
    }

    mw_notify->setChecked(m_manager->settings()->notify);
    mw_showThumbnails->setChecked(m_manager->settings()->showThumbnails);
    mw_alwaysOnTop->setChecked(m_manager->settings()->windowAlwaysOnTop);

    mw_lang->addItems(SettingsManager::availableLanguages("Translations"));
    mw_lang->setCurrentText(m_manager->settings()->lang);
}

void SettingsDialog::saveSettings()
{
    m_manager->settings()->reinterpret = Core::ReinterpretData_None;

    if(mw_reinterpretUrl->isChecked()) {
        m_manager->settings()->reinterpret |= Core::ReinterpretData_TextToUrl;
    }

    if(mw_reinterpretColor->isChecked()) {
        m_manager->settings()->reinterpret |= Core::ReinterpretData_TextToColor;
    }

    m_manager->settings()->notify = mw_notify->isChecked();
    m_manager->settings()->showThumbnails = mw_showThumbnails->isChecked();
    m_manager->settings()->windowAlwaysOnTop = mw_alwaysOnTop->isChecked();

    m_manager->settings()->lang = mw_lang->currentText();

    m_manager->save();
}

void SettingsDialog::showAppInfos()
{
    QLabel *label = new QLabel(this);
    label->setText(tr("MiniClipBoard %1 %2").arg(Utils::appVersion()).arg(m_manager->lang()));
    label->setStyleSheet("padding-right: 10px;");

    mw_statusBar->addPermanentWidget(label);
}

SettingsManager *SettingsDialog::manager() const
{
    return m_manager;
}

void SettingsDialog::setManager(SettingsManager *manager)
{
    m_manager = manager;
}

void SettingsDialog::settingsUIChanged()
{
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>();
    connect(watcher, &QFutureWatcher<void>::finished, [=]() {
        delete watcher;
        emit settingsChanged();
    });

    QFuture<void> future = QtConcurrent::run(this, &SettingsDialog::saveSettings);
    watcher->setFuture(future);
}
