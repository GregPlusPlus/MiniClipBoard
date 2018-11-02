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
    $$PWD/MainWindow/underlyingwindow.cpp \
    $$PWD/MainWindow/mainwindow.cpp \
    $$PWD/MainWindow/titlebar.cpp \
    $$PWD/CoreUI/coreui.cpp \
    $$PWD/CoreUI/Widgets/flatactionbutton.cpp \
    $$PWD/CoreUI/Widgets/browsedialog.cpp \
    $$PWD/CoreUI/Widgets/infospopup.cpp \
    $$PWD/CoreUI/Widgets/linkbutton.cpp \
    $$PWD/CoreUI/Widgets/tooltipwindow.cpp \
    $$PWD/CoreUI/Widgets/lineedit.cpp \
    $$PWD/CoreUI/WidgetsManager/widgetsmanager.cpp \
    $$PWD/UtilsUI/utilsui.cpp \
    $$PWD/ListWidget/container.cpp \
    $$PWD/ListWidget/abstractlistedwidget.cpp \
    $$PWD/PopupWindow/tray.cpp \
    $$PWD/PopupWindow/popupwindow.cpp \
    $$PWD/DataWidget/datawidget.cpp \
    $$PWD/DataWidget/ThumbnailWidget/imagethumbnail.cpp \
    $$PWD/DataWidget/ThumbnailWidget/colorthumbnailwidget.cpp \
    $$PWD/NavTab/navtab.cpp \
    $$PWD/NavTab/tabbutton.cpp \
    $$PWD/SearchBox/searchbox.cpp \
    $$PWD/SearchBox/DateTimePicker/datetimepicker.cpp \
    $$PWD/DataWidgetContainer/datawidgetcontainer.cpp \
    $$PWD/DataWidgetContainer/headerwidget.cpp \
    $$PWD/ContentViewer/contentviewer.cpp \
    $$PWD/ContentViewer/Viewers/TextViewer/textviewer.cpp \
    $$PWD/ContentViewer/Viewers/HTMLViewer/htmlviewer.cpp \
    $$PWD/ContentViewer/Viewers/ImageViewer/imageviewer.cpp \
    $$PWD/ContentViewer/Viewers/ColorViewer/colorviewer.cpp \
    $$PWD/ContentViewer/Viewers/LinksViewer/linkviewer.cpp \
    $$PWD/ContentViewer/Viewers/LinksViewer/linksviewer.cpp \
    $$PWD/ContentViewer/Viewers/LinksViewer/FileViewer/fileviewer.cpp \
    $$PWD/ContentViewer/Viewers/LinksViewer/FileViewer/errorwidget.cpp \
    $$PWD/CloudPopup/cloudpopup.cpp \
    $$PWD/CloudPopup/platformselector.cpp \
    $$PWD/CloudPopup/Setting/pastebinsettings.cpp \
    $$PWD/Settings/settingsdialog.cpp \
    $$PWD/Settings/aboutdialog.cpp \
    $$PWD/Settings/creditsdialog.cpp \
    $$PWD/Settings/moreoptionsdialog.cpp \
    $$PWD/Settings/hotkeysdialog.cpp \
    $$PWD/Settings/cloudcredentialsdialog.cpp \
    $$PWD/Settings/pluginsinfodialog.cpp \
    $$PWD/LoaderScreen/loaderscreen.cpp \
    $$PWD/WelcomeScreen/welcomescreen.cpp \
    $$PWD/DownloadDialog/downloaddialog.cpp \
    $$PWD/Browser/browser.cpp \
    $$PWD/Browser/navbar.cpp \
    $$PWD/Browser/iconwidget.cpp \
    $$PWD/Browser/popup.cpp \
    $$PWD/Browser/urlbar.cpp \
    $$PWD/TooltipWindow/copytooltipwindow.cpp \
    $$PWD/BubbleSearch/bubblesearch.cpp \
    $$PWD/DragDropScreen/dragdropscreen.cpp

HEADERS += \
    $$PWD/MainWindow/underlyingwindow.h \
    $$PWD/MainWindow/mainwindow.h \
    $$PWD/MainWindow/titlebar.h \
    $$PWD/CoreUI/coreui.h \
    $$PWD/CoreUI/Widgets/flatactionbutton.h \
    $$PWD/CoreUI/Widgets/browsedialog.h \
    $$PWD/CoreUI/Widgets/infospopup.h \
    $$PWD/CoreUI/Widgets/linkbutton.h \
    $$PWD/CoreUI/Widgets/tooltipwindow.h \
    $$PWD/CoreUI/Widgets/lineedit.h \
    $$PWD/CoreUI/WidgetsManager/widgetsmanager.h \
    $$PWD/UtilsUI/utilsui.h \
    $$PWD/ListWidget/container.h \
    $$PWD/ListWidget/abstractlistedwidget.h \
    $$PWD/PopupWindow/tray.h \
    $$PWD/PopupWindow/popupwindow.h \
    $$PWD/DataWidget/datawidget.h \
    $$PWD/DataWidget/ThumbnailWidget/imagethumbnail.h \
    $$PWD/DataWidget/ThumbnailWidget/colorthumbnailwidget.h \
    $$PWD/NavTab/navtab.h \
    $$PWD/NavTab/tabbutton.h \
    $$PWD/SearchBox/searchbox.h \
    $$PWD/SearchBox/DateTimePicker/datetimepicker.h \
    $$PWD/DataWidgetContainer/datawidgetcontainer.h \
    $$PWD/DataWidgetContainer/headerwidget.h \
    $$PWD/ContentViewer/contentviewer.h \
    $$PWD/ContentViewer/Viewers/TextViewer/textviewer.h \
    $$PWD/ContentViewer/Viewers/HTMLViewer/htmlviewer.h \
    $$PWD/ContentViewer/Viewers/ImageViewer/imageviewer.h \
    $$PWD/ContentViewer/Viewers/ColorViewer/colorviewer.h \
    $$PWD/ContentViewer/Viewers/LinksViewer/linkviewer.h \
    $$PWD/ContentViewer/Viewers/LinksViewer/linksviewer.h \
    $$PWD/ContentViewer/Viewers/LinksViewer/FileViewer/fileviewer.h \
    $$PWD/ContentViewer/Viewers/LinksViewer/FileViewer/errorwidget.h \
    $$PWD/CloudPopup/cloudpopup.h \
    $$PWD/CloudPopup/platformselector.h \
    $$PWD/CloudPopup/Setting/pastebinsettings.h \
    $$PWD/Settings/settingsdialog.h \
    $$PWD/Settings/aboutdialog.h \
    $$PWD/Settings/creditsdialog.h \
    $$PWD/Settings/moreoptionsdialog.h \
    $$PWD/Settings/hotkeysdialog.h \
    $$PWD/Settings/cloudcredentialsdialog.h \
    $$PWD/Settings/pluginsinfodialog.h \
    $$PWD/LoaderScreen/loaderscreen.h \
    $$PWD/WelcomeScreen/welcomescreen.h \
    $$PWD/DownloadDialog/downloaddialog.h \
    $$PWD/Browser/browser.h \
    $$PWD/Browser/navbar.h \
    $$PWD/Browser/iconwidget.h \
    $$PWD/Browser/popup.h \
    $$PWD/Browser/urlbar.h \
    $$PWD/TooltipWindow/copytooltipwindow.h \
    $$PWD/BubbleSearch/bubblesearch.h \
    $$PWD/DragDropScreen/dragdropscreen.h
