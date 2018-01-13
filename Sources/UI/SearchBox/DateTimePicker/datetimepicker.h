#ifndef DATETIMEPICKER_H
#define DATETIMEPICKER_H

#include <QWidget>
#include <QLabel>
#include <QDateTimeEdit>
#include <QComboBox>

#include <QGridLayout>

#include "../../../Core/core.h"
#include "../../../Utils/utils.h"

class DateTimePicker : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimePicker(QWidget *parent = nullptr);
    Core::DateTimeFilter getDateTimeFilter();
signals:
    void dateTimeFilterChanged(const Core::DateTimeFilter &filter);

public slots:
    void updateMode(int index);
    void updateDateTimeFilter();

private:
    QGridLayout *m_layout;

    QComboBox *mw_mode;

    QDateTimeEdit *mw_dt_1;
    QDateTimeEdit *mw_dt_2;

    Core::DateTimeFilterType m_mode;
};

#endif // DATETIMEPICKER_H
