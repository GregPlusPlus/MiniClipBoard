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

SettingsDialog::SettingsDialog(SettingsManager *settingsManager, BookmarkManager *bmManager, QWidget *parent) : QDialog(parent), m_settingsManager(settingsManager), m_bmManager(bmManager)
{
    setWindowIcon(QIcon(":/icons/ic_help_outline_white_18dp"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setMinimumWidth(350);

    mw_scroll = new QScrollArea(this);
    mw_scroll->setWidgetResizable(true);

    mw_widget = new QWidget(mw_scroll);

    m_layoutScroll = new QVBoxLayout;
    m_layoutScroll->setMargin(0);

    m_mainLayout = new QVBoxLayout;
    //m_mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_mainLayout->setMargin(0);

    m_layout = new QVBoxLayout;
    m_layout->setMargin(10);

    mw_reinterpretGroup = new QGroupBox(tr("Reinterpret data"), this);
    m_reinterpretLayout = new QVBoxLayout;
    mw_reinterpretGroup->setLayout(m_reinterpretLayout);

    mw_reinterpretUrl = new QCheckBox(tr("Reinterpret text as URL"), this);
    mw_reinterpretColor = new QCheckBox(tr("Reinterpret text as color"), this);

    m_reinterpretLayout->addWidget(mw_reinterpretUrl);
    m_reinterpretLayout->addWidget(mw_reinterpretColor);

    mw_notify = new QCheckBox(tr("Notify each time there is a new copy"), this);

    mw_showThumbnails = new QCheckBox(tr("Show thumbnails"), this);

    mw_alwaysOnTop = new QCheckBox(tr("Window always on top"), this);

    mw_langGroup = new QGroupBox(tr("Language"), this);
    m_langLayout = new QHBoxLayout;
    mw_langGroup->setLayout(m_langLayout);

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

    mw_bookmarksGroup = new QGroupBox(tr("Bookmarks"), this);
    m_bookmarksLayout = new QVBoxLayout;

    mw_exportBookmarks = new QPushButton(tr("Export bookmarks"));
    mw_importBookmarks = new QPushButton(tr("Import bookmarks"));
    mw_bmPath = new QLineEdit(m_bmManager->dir().absolutePath(), this);
    mw_bmPath->setReadOnly(true);
    mw_bmPath->setStyleSheet("border: none;"
                             "background: rgba(20, 20, 20, 120);");

    m_bookmarksLayout->addWidget(mw_exportBookmarks);
    m_bookmarksLayout->addWidget(mw_importBookmarks);
    m_bookmarksLayout->addWidget(new QLabel(tr("Bookmarks directory :"), this));
    m_bookmarksLayout->addWidget(mw_bmPath);

    mw_bookmarksGroup->setLayout(m_bookmarksLayout);

    mw_updatesGroup = new QGroupBox(tr("Updates"), this);
    m_updatesLayout = new QVBoxLayout;

    mw_autoUpdates = new QCheckBox(tr("Auto check updates"), this);

    mw_checkForUpdates = new QPushButton(tr("Check for updates"), this);
    connect(mw_checkForUpdates, SIGNAL(clicked(bool)), this, SIGNAL(checkForUpdates()));

    m_updatesLayout->addWidget(mw_autoUpdates);
    m_updatesLayout->addWidget(mw_checkForUpdates);

    mw_updatesGroup->setLayout(m_updatesLayout);

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

    m_layout->addWidget(mw_reinterpretGroup);
    m_layout->addWidget(mw_notify);
    m_layout->addWidget(mw_showThumbnails);
    m_layout->addWidget(mw_alwaysOnTop);
    m_layout->addWidget(mw_langGroup);
    m_layout->addWidget(mw_bookmarksGroup);
    m_layout->addWidget(mw_updatesGroup);
    m_layout->addWidget(UtilsUI::createSeparator());
    m_layout->addWidget(mw_legalInfosGroup);

    mw_statusBar = new QStatusBar(this);
    mw_statusBar->setSizeGripEnabled(false);
    showAppInfos();

    m_mainLayout->addLayout(m_layout);

    mw_widget->setLayout(m_mainLayout);

    mw_scroll->setWidget(mw_widget);

    m_layoutScroll->addWidget(mw_scroll);
    m_layoutScroll->addWidget(mw_statusBar);

    setLayout(m_layoutScroll);

    initUISettings();

    connect(mw_reinterpretUrl, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_reinterpretColor, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_notify, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_showThumbnails, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_alwaysOnTop, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_autoUpdates, SIGNAL(toggled(bool)), this, SLOT(settingsUIChanged()));
    connect(mw_lang, SIGNAL(activated(QString)), this, SLOT(settingsUIChanged()));
    connect(mw_exportBookmarks, SIGNAL(clicked(bool)), this, SLOT(exportBookmarks()));
    connect(mw_importBookmarks, SIGNAL(clicked(bool)), this, SLOT(importBookmarks()));
}

void SettingsDialog::initUISettings()
{
    if((m_settingsManager->settings()->reinterpret & Core::ReinterpretData_TextToUrl) != 0) {
        mw_reinterpretUrl->setChecked(true);
    }

    if((m_settingsManager->settings()->reinterpret & Core::ReinterpretData_TextToColor) != 0) {
        mw_reinterpretColor->setChecked(true);
    }

    mw_notify->setChecked(m_settingsManager->settings()->notify);
    mw_showThumbnails->setChecked(m_settingsManager->settings()->showThumbnails);
    mw_alwaysOnTop->setChecked(m_settingsManager->settings()->windowAlwaysOnTop);
    mw_autoUpdates->setChecked(m_settingsManager->settings()->autoCheckUpdates);

    mw_lang->addItems(SettingsManager::availableLanguages("Translations"));
    mw_lang->setCurrentText(m_settingsManager->settings()->lang);
}

void SettingsDialog::saveSettings()
{
    m_settingsManager->settings()->reinterpret = Core::ReinterpretData_None;

    if(mw_reinterpretUrl->isChecked()) {
        m_settingsManager->settings()->reinterpret |= Core::ReinterpretData_TextToUrl;
    }

    if(mw_reinterpretColor->isChecked()) {
        m_settingsManager->settings()->reinterpret |= Core::ReinterpretData_TextToColor;
    }

    m_settingsManager->settings()->notify = mw_notify->isChecked();
    m_settingsManager->settings()->showThumbnails = mw_showThumbnails->isChecked();
    m_settingsManager->settings()->windowAlwaysOnTop = mw_alwaysOnTop->isChecked();
    m_settingsManager->settings()->autoCheckUpdates = mw_autoUpdates->isChecked();

    m_settingsManager->settings()->lang = mw_lang->currentText();

    m_settingsManager->save();
}

void SettingsDialog::showAppInfos()
{
    QLabel *label = new QLabel(this);
    label->setText(tr("MiniClipBoard V%1 %2").arg(Utils::appVersion()).arg(m_settingsManager->lang()));
    label->setStyleSheet("padding-right: 10px;");

    mw_statusBar->addPermanentWidget(label);
}

SettingsManager *SettingsDialog::manager() const
{
    return m_settingsManager;
}

void SettingsDialog::setManager(SettingsManager *manager)
{
    m_settingsManager = manager;
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

void SettingsDialog::exportBookmarks()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Export to ... - Select directory"),
                                                    QString(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    m_bmManager->exportBookmarks(QDir(dir));
}

void SettingsDialog::importBookmarks()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Import from ... - Select directory"),
                                                    QString(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    m_bmManager->importBookmarks(QDir(dir));
}
