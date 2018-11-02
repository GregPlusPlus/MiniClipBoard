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

#-------------------------------------------------
#
# Project created by QtCreator 2018-09-15T23:41:12
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = AudioViewer
TEMPLATE = lib
CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

Debug:DESTDIR = ../../debug/plugins
Release:DESTDIR = ../../release/plugins

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/audioviewer.cpp \
    $$PWD/audiowidget.cpp \
    $$PWD/PlayerWidget/playerwidget.cpp \
    $$PWD/PlayerWidget/popupvolume.cpp \
    $$PWD/PlayerWidget/flatactionbutton.cpp \
    $$PWD/PlayerWidget/infospopup.cpp


HEADERS += \
    $$PWD/audioviewer.h \
    $$PWD/audiowidget.h \
    $$PWD/PlayerWidget/playerwidget.h \
    $$PWD/PlayerWidget/popupvolume.h \
    $$PWD/PlayerWidget/flatactionbutton.h \
    $$PWD/PlayerWidget/infospopup.h

DISTFILES += AudioViewer.json
