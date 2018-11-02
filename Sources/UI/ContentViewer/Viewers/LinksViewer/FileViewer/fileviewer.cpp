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

#include "fileviewer.h"

FileViewer::FileViewer(const QUrl &url, const Plugins::Plugins &plugins, QWidget *parent)
    : QWidget(parent), m_plugins(plugins)
{
    m_layout = new QGridLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    setViewer(url);

    mw_closeButton = new QPushButton(tr("Close preview"), this);
    connect(mw_closeButton, &QPushButton::clicked, [=]() {
        QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
        setGraphicsEffect(opacity);
        opacity->setOpacity(0);
        QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity");
        anim->setDuration(200);
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->start(QPropertyAnimation::DeleteWhenStopped);
        connect(anim, &QPropertyAnimation::finished, [=]() {
            emit closeViewer(this);
            deleteLater();
        });
    });

    m_layout->addWidget(mw_viewer, 0, 0, 1, 4);
    m_layout->addWidget(mw_closeButton, 1, 0, 1, 4);

    setLayout(m_layout);

    show();
}

void FileViewer::show()
{
    QWidget::show();

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacity);
    opacity->setOpacity(0);
    QPropertyAnimation *anim = new QPropertyAnimation(opacity, "opacity");
    anim->setDuration(200);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QPropertyAnimation::DeleteWhenStopped);
}

void FileViewer::setViewer(const QUrl &url)
{
    switch (Core::getFileType(url, m_plugins)) {
    case Core::FileType_Image:
    {
        mw_viewer = new ImageViewer(QPixmap(url.toLocalFile()), this);
    }
        break;
    case Core::FileType_Html:
    {
        Browser *browser = new Browser(this);
        browser->setUrl(url.toString());
        browser->setControls(NavBar::Controls_NoControls);
        mw_viewer = browser;
    }
        break;
    case Core::FileType_Text:
    {
        QFile f(url.toLocalFile());
        if(f.open(QIODevice::ReadOnly)) {
            mw_viewer = new TextViewer(f.readAll(), this);
        }
    }
        break;
    case Core::FileType_FromPlugin:
    {
        mw_viewer = searchPluginsWidget(url);
        if(!mw_viewer) {
            mw_viewer = new ErrorWidget(ErrorWidget::ErrType_BadPlugin, url.toLocalFile(), this);
        }
    }
        break;
    default:
    {
        mw_viewer = new ErrorWidget(ErrorWidget::ErrType_Unknown, url.toLocalFile(), this);
    }
        break;
    }

    if(!mw_viewer) {
        mw_viewer = new ErrorWidget(ErrorWidget::ErrType_NotFound, url.toLocalFile(), this);
    }
}

QWidget *FileViewer::searchPluginsWidget(const QUrl &url)
{
    for(Plugins::Plugin plugin : m_plugins) {
        PluginViewerInterface *interface = plugin.interface;

        if(interface->supportedFormats().contains(QFileInfo(url.toString()).suffix().toLower())) {
            return interface->widget(url, this);
        }
    }

    return nullptr;
}
