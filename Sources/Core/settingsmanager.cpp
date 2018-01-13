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

#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    m_settings.reinterpret = (Core::ReinterpretData)(Core::ReinterpretData_TextToUrl | Core::ReinterpretData_TextToColor);
    m_settings.notify = true;
    m_settings.firstStart = true;
    m_settings.showThumbnails = true;
    m_settings.windowAlwaysOnTop = true;
    m_settings.lang = "en";
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

    for(int i = 0; i < files.count(); i++) {
        QString fileName = files.at(i);
        if(fileName.right(2) == "qm") {
            langs.append(fileName.right(5).left(2));
        }
    }

    return langs;
}

void SettingsManager::load()
{
    QSettings qsettings(m_filename, QSettings::IniFormat);

    m_settings.reinterpret = qsettings.value("Settings/Reinterpret", 3).toInt();
    m_settings.notify = qsettings.value("Settings/Notify", true).toBool();
    m_settings.showThumbnails = qsettings.value("Settings/ShowThumbnails", true).toBool();
    m_settings.windowAlwaysOnTop = qsettings.value("Settings/WindowAlwaysOnTop", true).toBool();

    m_settings.firstStart = qsettings.value("AppState/FirstStart", true).toBool();

    m_settings.lang = qsettings.value("Language/CurrentLanguage", "AUTO").toString();
}

void SettingsManager::save()
{
    QSettings qsettings(m_filename, QSettings::IniFormat);

    qsettings.beginGroup("Settings");
    qsettings.setValue("Reinterpret", m_settings.reinterpret);
    qsettings.setValue("Notify", m_settings.notify);
    qsettings.setValue("ShowThumbnails", m_settings.showThumbnails);
    qsettings.setValue("WindowAlwaysOnTop", m_settings.windowAlwaysOnTop);
    qsettings.endGroup();

    qsettings.beginGroup("AppState");
    qsettings.setValue("FirstStart", m_settings.firstStart);
    qsettings.endGroup();

    qsettings.beginGroup("Language");
    qsettings.setValue("CurrentLanguage", m_settings.lang);
}
