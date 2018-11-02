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

#ifndef CONTENTVIEWER_H
#define CONTENTVIEWER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QFileDialog>

#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QPaintEvent>

#include <QPropertyAnimation>

#include <QDateTime>

#include <QFile>

#include <QDebug>

#include "../../Core/Core/core.h"
#include "../../Core/PrintManager/printmanager.h"
#include "../../Cloud/cloud.h"
#include "../../plugins/pluginsutils.h"
#include "../CoreUI/Widgets/flatactionbutton.h"

#include "Viewers/TextViewer/textviewer.h"
#include "Viewers/HTMLViewer/htmlviewer.h"
#include "Viewers/ImageViewer/imageviewer.h"
#include "Viewers/LinksViewer/linksviewer.h"
#include "Viewers/ColorViewer/colorviewer.h"
#include "../CloudPopup/cloudpopup.h"

class ContentViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ContentViewer(const Plugins::Plugins &plugins, QWidget *parent = nullptr);
    ~ContentViewer();

    Core::ClipboardData data() const;
    void setData(const Core::ClipboardData &data);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);

    QString title() const;
    void setTitle(const QString &title);

    int animationDuration() const;
    void setAnimationDuration(int animationDuration);

signals:
    void closed();
    void upload(CloudTypes::CloudData &data);

public slots:
    void save();
    void print();
    void fadeIn();
    void fadeOut();

private:
    QWidget          *mw_header;

    QGridLayout      *m_headerLayout;

    QPushButton      *mw_quitButton;
    FlatActionButton *mw_saveButton;
    FlatActionButton *mw_printButton;
    FlatActionButton *mw_cloudButton;
    QLabel           *mw_title;
    QLabel           *mw_infosLabel;
    QWidget          *mw_viewer;

    CloudPopup       *mw_cloudPopup;

    Core::ClipboardData m_data;

    Plugins::Plugins m_plugins;

    QString m_title;
    QDateTime m_dateTime;

    int m_headerHeight = 69;
    int m_animationDuration;

private:
    void applyMask();
    void displayInfos();
    void displayData();

    QString elidedText(const QString &text, QLabel *label);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // CONTENTVIEWER_H
