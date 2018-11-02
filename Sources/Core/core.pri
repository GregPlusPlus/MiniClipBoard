#************************ LICENSING & COPYRIGHT ***********************
# Copyright © 2017-2018 Grégoire BOST
#
# This file is part of MiniClipBoard.
#
# MiniClipBoard is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MiniClipBoard is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with MiniClipBoard.  If not, see <http://www.gnu.org/licenses/>.
#***********************************************************************

SOURCES += \
    $$PWD/Core/core.cpp \
    $$PWD/BookmarkManager/bookmarkmanager.cpp \
    $$PWD/SettingsManager/settingsmanager.cpp \
    $$PWD/Updater/updater.cpp \
    $$PWD/Updater/UpdaterUtils/updaterutils.cpp \
    $$PWD/UniqueProcessChecker/uniqueprocesschecker.cpp \
    $$PWD/HotKeysManager/hotkeysmanager.cpp\
    $$PWD/HotKeysManager/hotkeysutils.cpp \
    $$PWD/PrintManager/printmanager.cpp \
    $$PWD/ProcessUtils/processutils.cpp \
    $$PWD/ExcludedProcessesManager/excludedprocessesmanager.cpp \
    $$PWD/ThreadLoader/threadloader.cpp

HEADERS += \
    $$PWD/Core/core.h \
    $$PWD/CoreTypes/coretypes.h \
    $$PWD/CoreTypes/clipboarddata.h \
    $$PWD/BookmarkManager/bookmarkmanager.h \
    $$PWD/SettingsManager/settingsmanager.h \
    $$PWD/Updater/updater.h \
    $$PWD/Updater/UpdaterUtils/updaterutils.h \
    $$PWD/UniqueProcessChecker/uniqueprocesschecker.h \
    $$PWD/HotKeysManager/hotkeysmanager.h \
    $$PWD/HotKeysManager/hotkeysutils.h \
    $$PWD/PrintManager/printmanager.h \
    $$PWD/ProcessUtils/processutils.h \
    $$PWD/ExcludedProcessesManager/excludedprocessesmanager.h \
    $$PWD/ThreadLoader/threadloader.h
