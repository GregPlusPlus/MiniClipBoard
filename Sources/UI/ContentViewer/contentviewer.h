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

#ifndef CONTENTVIEWER_H
#define CONTENTVIEWER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QFileDialog>

#include <Qpainter>
#include <QPen>
#include <QBrush>

#include <QPaintEvent>

#include <QPropertyAnimation>

#include <QDateTime>

#include <QFile>

#include <QDebug>

#include "../../Core/core.h"
#include "TextViewer/textviewer.h"
#include "HTMLViewer/htmlviewer.h"
#include "ImageViewer/imageviewer.h"
#include "LinksViewer/linksviewer.h"
#include "ColorViewer/colorviewer.h"

class ContentViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ContentViewer(QWidget *parent = nullptr);

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

public slots:
    void save();
    void fadeIn();
    void fadeOut();

private:
    QWidget *mw_header;

    QGridLayout *m_headerLayout;

    QPushButton *mw_quitButton;
    QLabel *mw_title;
    QLabel *mw_infosLabel;
    QPushButton *mw_saveButton;
    QWidget *mw_viewer;

    Core::ClipboardData m_data;

    QString m_title;
    QDateTime m_dateTime;

    int m_headerHeight;
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
