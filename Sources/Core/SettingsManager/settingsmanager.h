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

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>

#include <QSettings>

#include <QDir>

#include <QMessageBox>

#include "../Core/core.h"

class SettingsManager
{
public:
    SettingsManager();

    Core::Settings *settings();
    void setSettings(const Core::Settings &settings);

    QString filename() const;
    void setFilename(const QString &filename);

    QString lang();
    static QStringList availableLanguages(const QString &dirName);

public slots:
    void load();
    void save();

private:
    QString m_filename;
    Core::Settings m_settings;
};

#endif // SETTINGSMANAGER_H
