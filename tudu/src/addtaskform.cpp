#include "headers/addtaskform.h"
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
    ui->dateEdit->setDate(m_date);
    ui->timeEdit->setTime(m_time);


    // Suppose it's a one-day task
    ui->dateEdit_2->setDate(m_date);

    // By deafult set end time +15min from start time
    ui->timeEdit_2->setTime(m_time.addSecs(5*MINUTE));
}

AddTaskForm::~AddTaskForm()
{
    delete ui;
}

void AddTaskForm::on_pbSaveTask_clicked()
{
    QString taskTitle = ui->taskTitle->text();
    QString taskDesc = ui->taskDesc->toPlainText();

    emit sendToCalendar(taskTitle, m_row, m_column);

    close();
}
