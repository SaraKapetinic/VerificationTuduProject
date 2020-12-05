#ifndef ADDTASKFORM_H
#define ADDTASKFORM_H

#include <QDialog>
#include <iostream>
#include <QDate>
#include "ui_mainwindow.h"

namespace Ui {
class AddTaskForm;
}

class AddTaskForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskForm(QWidget *parent = 0, QTime time = QTime(0,0), QDate date = QDate(0,0,0), int row = 0, int column = 0);
    ~AddTaskForm();

private slots:
    void on_pbSaveTask_clicked();

signals:
    void sendToCalendar(QString taskTitle, int row, int column);

private:
    Ui::AddTaskForm *ui;
    QTime m_time;
    QDate m_date;
    int m_row;
    int m_column;
};

#endif // ADDTASKFORM_H
