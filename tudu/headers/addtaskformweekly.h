#ifndef ADDTASKFORMWEEKLY_H
#define ADDTASKFORMWEEKLY_H

#include <QDialog>
#include <iostream>
#include <QDate>
#include "ui_mainwindow.h"

namespace Ui {
class AddTaskFormWeekly;
}

class AddTaskFormWeekly : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskFormWeekly(QWidget *parent = 0, QTime time = QTime(0,0), QDate date = QDate(0,0,0), int row = 0, int column = 0);
    ~AddTaskFormWeekly();

private slots:
    void on_pbSaveTask_clicked();

signals:
    void sendToCalendar(QString taskTitle, int row, int column, int span);

private:
    Ui::AddTaskFormWeekly *ui;
    QTime m_time;
    QDate m_date;
    int m_row;
    int m_column;
};

#endif // ADDTASKFORMWEEKLY_H
