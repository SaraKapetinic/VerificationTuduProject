#ifndef INIT_H
#define INIT_H

#include<iostream>
#include <QWidget>
#include <QDate>
#include <QColor>
#include "ui_mainwindow.h"

#define NUM_OF_WEEKDAYS 7
#define HOURS_IN_DAY 24
#define MINUTES_IN_HOUR 60
#define MINUTE_INCREMENTS 15
#define SECONDS_IN_MINUTE 60

class Init
{
public:
    Init();

    void setDays(Ui::MainWindow* ui);
    void setHeaders(Ui::MainWindow* ui);
    void setDesign(Ui::MainWindow* ui);

    QList<QDate> getCurrentWeek();

    int getCurrentTimeRow(Ui::MainWindow* ui);
    int getCurrentDayOfWeek(Ui::MainWindow* ui);

private:
    QWidget m_ui;
    QStringList m_horizontalHeaders;
    QStringList m_verticalHeaders;
    QList<QDate> m_currentWeek;
};

#endif // INIT_H
