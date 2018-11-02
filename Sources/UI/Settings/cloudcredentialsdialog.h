#ifndef CLOUDCREDENTIALSDIALOG_H
#define CLOUDCREDENTIALSDIALOG_H

#include <QDialog>
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

#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QIcon>

#include "../../Cloud/cloudutils.h"
#include "../../Cloud/cloud.h"
#include "../CoreUI/Widgets/lineedit.h"
#include "../CoreUI/Widgets/flatactionbutton.h"

class CloudCredentialsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloudCredentialsDialog(QWidget *parent = nullptr);

signals:

public slots:
    void savePastebinKey();

private:
    QVBoxLayout      *m_layout;

    QGridLayout      *m_pastebinLayout;
    QGroupBox        *mw_pastebinGroup;
    LineEdit         *mw_pastebinApiKey;
    FlatActionButton *mw_pastebinApiKeySave;
    QPushButton      *mw_pastebinHelpButton;

private:
    void init();
};

#endif // CLOUDCREDENTIALSDIALOG_H
