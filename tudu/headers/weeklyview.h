#ifndef WEEKLYVIEW_H
#define WEEKLYVIEW_H

#include <iostream>
#include <QWidget>
#include <QDate>
#include <QColor>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include "ui_mainwindow.h"
#include "headers/task.h"

#define NUM_OF_WEEKDAYS (7)
#define HOURS_IN_DAY (24)
#define MINUTES_IN_HOUR (60)
#define MINUTE_INCREMENTS (15)
#define SECONDS_IN_MINUTE (60)

class WeeklyView
{
public:
    WeeklyView(Ui::MainWindow* ui);
    WeeklyView(Ui::MainWindow* ui, QDate date);

    void clearView();
    void setDays();
    void setHeaders();
    void setDesign();
    void loadFromJson();

    void execute();

    QList<QDate> getCurrentWeek() const;

    int getCurrentTimeRow() const;

    int getCurrentDayOfWeek() const;

private:
    Ui::MainWindow* m_ui;
    QStringList m_horizontalHeaders;
    QStringList m_verticalHeaders;
    QList<QDate> m_currentWeek;
    QDate m_selectedDate;
    QList<Task> m_weeklyTasks;
    QColor m_headerPrimaryColor = QColor(225, 239, 230);
    QColor m_headerSecondaryColor = QColor(22, 12, 40);
};

#endif // WEEKLYVIEW_H
