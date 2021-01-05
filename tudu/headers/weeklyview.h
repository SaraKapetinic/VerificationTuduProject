#ifndef WEEKLYVIEW_H
#define WEEKLYVIEW_H

#include <iostream>
#include <QWidget>
#include <QDate>
#include <QColor>
#include "ui_mainwindow.h"

#define NUM_OF_WEEKDAYS (7)
#define HOURS_IN_DAY (24)
#define MINUTES_IN_HOUR (60)
#define MINUTE_INCREMENTS (15)
#define SECONDS_IN_MINUTE (60)

class WeeklyView
{
public:
    WeeklyView();
    WeeklyView(QDate date);

    void setDays(Ui::MainWindow* ui);
    void setHeaders(Ui::MainWindow* ui);
    void setDesign(Ui::MainWindow* ui);

    void execute(Ui::MainWindow* ui);

    QList<QDate> getCurrentWeek();

    int getCurrentTimeRow();

    int getCurrentDayOfWeek();

private:
    QWidget m_ui;
    QStringList m_horizontalHeaders;
    QStringList m_verticalHeaders;
    QList<QDate> m_currentWeek;
    QDate m_selectedDate;
};

#endif // WEEKLYVIEW_H
