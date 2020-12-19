#include "headers/addtaskformweekly.h"
#include "ui_addtaskform.h"
#include "ui_mainwindow.h"
#include "headers/init.h"


AddTaskForm::AddTaskForm(QWidget *parent, QTime time, QDate date, int row, int column) :
    QDialog(parent),
    ui(new Ui::AddTaskForm)
{
    m_time = time;
    m_date = date;
    m_row = row;
    m_column = column;

    ui->setupUi(this);

    // Fill out form with time and date based on clicked cell
    ui->startDate->setDate(m_date);
    ui->startTime->setTime(m_time);




    // Suppose it's a one-day task
    ui->endDate->setDate(m_date);

    // By deafult set end time +15min from start time
    ui->endTime->setTime(m_time.addSecs(15*SECONDS_IN_MINUTE));
}

AddTaskForm::~AddTaskForm()
{
    delete ui;
}

void AddTaskForm::on_pbSaveTask_clicked()
{
    QString taskTitle = ui->taskTitle->text();
    QString taskDesc = ui->taskDesc->toPlainText();

    int start = ui->startTime->time().hour() * 60 + ui->startTime->time().minute();
    int end = ui->endTime->time().hour() * 60 + ui->endTime->time().minute();
    int span = (end - start)/15;

    emit sendToCalendar(taskTitle, m_row, m_column, span);

    close();
}
