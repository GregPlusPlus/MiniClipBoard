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

#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    m_settings.reinterpret          = (Core::ReinterpretData)(Core::ReinterpretData_TextToUrl | Core::ReinterpretData_TextToColor);
    m_settings.clipboardTimeOut     = QTime(0, 0, 0, 0);
    m_settings.notify               = true;
    m_settings.firstStart           = true;
    m_settings.showThumbnails       = true;
    m_settings.windowAlwaysOnTop    = true;
    m_settings.tooltipCopy          = true;
    m_settings.autoCheckUpdates     = true;
    m_settings.timeOutEnabled       = false;
    m_settings.excludeProcesses     = true;
    m_settings.lang                 = "en";
}

Core::Settings* SettingsManager::settings()
{
    return &m_settings;
}

void SettingsManager::setSettings(const Core::Settings &settings)
{
    m_settings = settings;
}

QString SettingsManager::filename() const
{
    return m_filename;
}

void SettingsManager::setFilename(const QString &filename)
{
    m_filename = filename;
}

QString SettingsManager::lang()
{
    if(m_settings.lang == "AUTO") {
        return QLocale::system().name().section('_', 0, 0);
    }

    return m_settings.lang;
}

QStringList SettingsManager::availableLanguages(const QString &dirName)
{
    QStringList langs;
    QDir dir(dirName);

    QStringList files = dir.entryList(QDir::Files);

    for(QString file : files) {
        if(file.contains(QRegExp("^(MiniClipBoard_{1})[a-z]{2}(\\.qm{1})$"))) {
            langs.append(file.right(5).left(2));
        }
    }

    return langs;
}

void SettingsManager::load()
{
    QSettings settings(m_filename, QSettings::IniFormat);

    m_settings.reinterpret          = settings.value("Settings/Reinterpret",        3                   ).toInt();
    m_settings.notify               = settings.value("Settings/Notify",             true                ).toBool();
    m_settings.showThumbnails       = settings.value("Settings/ShowThumbnails",     true                ).toBool();
    m_settings.windowAlwaysOnTop    = settings.value("Settings/WindowAlwaysOnTop",  true                ).toBool();
    m_settings.tooltipCopy          = settings.value("Settings/TooltipCopy",        true                ).toBool();
    m_settings.autoCheckUpdates     = settings.value("Settings/AutoCheckUpdates",   true                ).toBool();

    m_settings.firstStart           = settings.value("AppState/FirstStart",         true                ).toBool();

    m_settings.clipboardTimeOut     = settings.value("General/ClipboardTimeOut",    QTime(0, 0, 0, 0)   ).toTime();
    m_settings.timeOutEnabled       = settings.value("General/TimeOutEnabled",      false               ).toBool();
    m_settings.excludeProcesses     = settings.value("General/ExcludeProcesses",    true                ).toBool();

    m_settings.lang                 = settings.value("Language/CurrentLanguage",    "AUTO"              ).toString();
}

void SettingsManager::save()
{
    QSettings settings(m_filename, QSettings::IniFormat);

    settings.beginGroup("Settings");
    settings.setValue("Reinterpret",        m_settings.reinterpret);
    settings.setValue("Notify",             m_settings.notify);
    settings.setValue("ShowThumbnails",     m_settings.showThumbnails);
    settings.setValue("WindowAlwaysOnTop",  m_settings.windowAlwaysOnTop);
    settings.setValue("TooltipCopy",        m_settings.tooltipCopy);
    settings.setValue("AutoCheckUpdates",   m_settings.autoCheckUpdates);
    settings.endGroup();

    settings.beginGroup("AppState");
    settings.setValue("FirstStart",         m_settings.firstStart);
    settings.endGroup();

    settings.beginGroup("General");
    settings.setValue("ClipboardTimeOut",   m_settings.clipboardTimeOut);
    settings.setValue("TimeOutEnabled",     m_settings.timeOutEnabled);
    settings.setValue("ExcludeProcesses",   m_settings.excludeProcesses);
    settings.endGroup();

    settings.beginGroup("Language");
    settings.setValue("CurrentLanguage",    m_settings.lang);
}
