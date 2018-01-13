#ifndef CREDITSDIALOG_H
#define CREDITSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>

#include <QGridLayout>

#include <QIcon>
#include <QFont>

class CreditsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreditsDialog(QWidget *parent = nullptr);

signals:

public slots:

private:
    QGridLayout *m_layout;

    QLabel *mw_text;
};

#endif // CREDITSDIALOG_H
