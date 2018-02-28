#************************ LICENSING & COPYRIGHT ***********************
# Copyright © 2017 Grégoire BOST
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
# Project created by QtCreator 2017-11-08T18:19:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml network

TARGET = MiniClipBoard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        Sources/mainwindow.cpp \
        Sources/main.cpp \
        Sources/Core/core.cpp \
        Sources/Core/bookmarkmanager.cpp \
        Sources/Core/settingsmanager.cpp \
        Sources/Core/updater.cpp \
        Sources/Core/UpdaterUtils/updaterutils.cpp \
        Sources/Utils/utils.cpp \
        Sources/UI/UtilsUI/utilsui.cpp \
        Sources/UI/ListWidget/container.cpp \
        Sources/UI/ListWidget/abstractlistedwidget.cpp \
        Sources/UI/PopupWindow/tray.cpp \
        Sources/UI/PopupWindow/popupwindow.cpp \
        Sources/UI/DataWidget/datawidget.cpp \
        Sources/UI/DataWidget/ThumbnailWidget/imagethumbnail.cpp \
        Sources/UI/DataWidget/ThumbnailWidget/colorthumbnailwidget.cpp \
        Sources/UI/NavTab/navtab.cpp \
        Sources/UI/NavTab/tabbutton.cpp \
        Sources/UI/CoreUI/coreui.cpp \
        Sources/UI/SearchBox/searchbox.cpp \
        Sources/UI/SearchBox/DateTimePicker/datetimepicker.cpp \
        Sources/UI/DataWidgetContainer/datawidgetcontainer.cpp \
        Sources/UI/ContentViewer/contentviewer.cpp \
        Sources/UI/ContentViewer/TextViewer/textviewer.cpp \
        Sources/UI/ContentViewer/HTMLViewer/htmlviewer.cpp \
        Sources/UI/ContentViewer/ImageViewer/imageviewer.cpp \
        Sources/UI/ContentViewer/ColorViewer/colorviewer.cpp \
        Sources/UI/ContentViewer/LinksViewer/linkviewer.cpp \
        Sources/UI/ContentViewer/LinksViewer/linksviewer.cpp \
        Sources/UI/Settings/settingsdialog.cpp \
        Sources/UI/Settings/aboutdialog.cpp \
        Sources/UI/Settings/creditsdialog.cpp \
        Sources/UI/LoaderScreen/loaderscreen.cpp \
        Sources/UI/WelcomeScreen/welcomescreen.cpp \
        Sources/UI/DownloadDialog/downloaddialog.cpp

HEADERS += \
        Sources/mainwindow.h \
        Sources/Core/coretypes.h \
        Sources/Core/core.h \
        Sources/Core/bookmarkmanager.h \
        Sources/Core/settingsmanager.h \
        Sources/Core/updater.h \
        Sources/Core/UpdaterUtils/updaterutils.h \
        Sources/Utils/legal.h \
        Sources/Utils/appinfos.h \
        Sources/Utils/utils.h \
        Sources/UI/UtilsUI/utilsui.h \
        Sources/UI/ListWidget/container.h \
        Sources/UI/ListWidget/abstractlistedwidget.h \
        Sources/UI/PopupWindow/tray.h \
        Sources/UI/PopupWindow/popupwindow.h \
        Sources/UI/DataWidget/datawidget.h \
        Sources/UI/DataWidget/ThumbnailWidget/imagethumbnail.h \
        Sources/UI/DataWidget/ThumbnailWidget/colorthumbnailwidget.h \
        Sources/UI/NavTab/navtab.h \
        Sources/UI/NavTab/tabbutton.h \
        Sources/UI/CoreUI/coreui.h \
        Sources/UI/SearchBox/searchbox.h \
        Sources/UI/SearchBox/DateTimePicker/datetimepicker.h \
        Sources/UI/DataWidgetContainer/datawidgetcontainer.h \
        Sources/UI/ContentViewer/contentviewer.h \
        Sources/UI/ContentViewer/TextViewer/textviewer.h \
        Sources/UI/ContentViewer/HTMLViewer/htmlviewer.h \
        Sources/UI/ContentViewer/ImageViewer/imageviewer.h \
        Sources/UI/ContentViewer/ColorViewer/colorviewer.h \
        Sources/UI/ContentViewer/LinksViewer/linkviewer.h \
        Sources/UI/ContentViewer/LinksViewer/linksviewer.h \
        Sources/UI/Settings/settingsdialog.h \
        Sources/UI/Settings/aboutdialog.h \
        Sources/UI/Settings/creditsdialog.h \
        Sources/UI/LoaderScreen/loaderscreen.h \
        Sources/UI/WelcomeScreen/welcomescreen.h \
        Sources/UI/DownloadDialog/downloaddialog.h

TRANSLATIONS += Translations/MiniClipBoard_fr.ts Translations/MiniClipBoard_es.ts

RESOURCES += \
    rc.qrc

win32 {
    OTHER_FILES += \
        win_rc.rc
    RC_FILE += \
        win_rc.rc
}
