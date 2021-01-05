#ifndef ADDTASKFORMWEEKLY_H
#define ADDTASKFORMWEEKLY_H

#include <QDialog>
#include <iostream>
#include <QDate>
#include "ui_mainwindow.h"
#include "task.h"

namespace Ui {
class AddTaskFormWeekly;
}

class AddTaskFormWeekly : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskFormWeekly(QWidget *parent = 0, QTime time = QTime(0,0), QDate date = QDate(0,0,0), int row = 0, int column = 0);
    ~AddTaskFormWeekly();
    void SetTaskTitle(QString TaskName);
    void SetTaskDescription(QString TaskDescription);
    void SetTaskStartTime(QDateTime TaskStartTime);
    void SetTaskEndTime(QDateTime TaskEndTime);

private slots:
    void on_pbSaveTask_clicked();

signals:
    void sendToCalendar(Task* task, int row, int column, int span);

private:
    Ui::AddTaskFormWeekly *ui;
    QTime m_time;
    QDate m_date;
    int m_row;
    int m_column;
};

#endif // ADDTASKFORMWEEKLY_H
