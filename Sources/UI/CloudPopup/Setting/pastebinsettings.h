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

#ifndef PASTEBINSETTINGS_H
#define PASTEBINSETTINGS_H

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QMessageBox>

#include <QGridLayout>
#include <QFormLayout>

#include "../../../Cloud/cloud.h"
#include "../../CoreUI/Widgets/lineedit.h"
#include "../../CoreUI/Widgets/flatactionbutton.h"

class PastebinSettings : public QWidget
{
    Q_OBJECT

public:
    explicit PastebinSettings(QWidget *parent = nullptr);

signals:
    void send(CloudTypes::CloudData &data);
    void cancel();

public slots:
    void upload();
    void checkKey();

private:
    QGridLayout      *m_layout;
    QFormLayout      *m_optionsLayout;

    QGroupBox        *mw_optionsGroup;
    FlatActionButton *mw_cancelButton;
    LineEdit         *mw_nameInput;
    FlatActionButton *mw_optionsButton;
    FlatActionButton *mw_sendButton;
    QPushButton      *mw_infosKeyButton;
    QPushButton      *mw_reloadKeyButton;
    QComboBox        *mw_expire;
    QComboBox        *mw_private;

private:
    void initOptions();
    void toggleOptions();
    void applyOptions(CloudTypes::CloudData &data);
};

#endif // PASTEBINSETTINGS_H
