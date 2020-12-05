#include "headers/addtaskform.h"
#include "ui_addtaskform.h"
#include "ui_mainwindow.h"

AddTaskForm::AddTaskForm(QWidget *parent, QTime time, QDate date, int row, int column) :
    QDialog(parent),
    ui(new Ui::AddTaskForm)
{
    m_time = time;
    m_date = date;
    m_row = row;
    m_column = column;

    ui->setupUi(this);

    // Fill out form with time and date
    ui->dateEdit->setDate(m_date);
    ui->timeEdit->setTime(m_time);
}

AddTaskForm::~AddTaskForm()
{
    delete ui;
}

void AddTaskForm::on_pbSaveTask_clicked()
{
    QString taskTitle = ui->taskTitle->text();

    emit sendToCalendar(taskTitle, m_row, m_column);

    close();
}
