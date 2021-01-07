#include "headers/addtaskformweekly.h"
#include "ui_addtaskformweekly.h"
#include "headers/weeklyview.h"
#include "headers/task.h"

AddTaskFormWeekly::AddTaskFormWeekly(QWidget *parent, QTime time, QDate date, int row, int column) :
    QDialog(parent),
    ui(new Ui::AddTaskFormWeekly)
{

    m_time = time;
    m_date = date;
    m_row = row;
    m_column = column;

    ui->setupUi(this);

    // Fill out form with time and date based on clicked cell
    ui->dateTimeStart->setDate(m_date);
    ui->dateTimeStart->setTime(m_time);

    // Suppose it's a one-day task
    ui->dateTimeEnd->setDate(m_date);

    // By deafult set end time +15min from start time
    ui->dateTimeEnd->setTime(m_time.addSecs(15*SECONDS_IN_MINUTE));
}

AddTaskFormWeekly::~AddTaskFormWeekly()
{
    delete ui;
}

void AddTaskFormWeekly::on_pbSaveTask_clicked()
{

    // Get task title and task description based on inputted data
    QString taskTitle = ui->taskTitle->text();
    QString taskDesc = ui->taskDesc->toPlainText();

    // Create span
    // Diff end and start and divide by 15 because one cell = 15 minutes
    int start = ui->dateTimeStart->time().hour() * MINUTES_IN_HOUR + ui->dateTimeStart->time().minute();
    int end = ui->dateTimeEnd->time().hour() * MINUTES_IN_HOUR + ui->dateTimeEnd->time().minute();
    int span = (end - start)/15;

    // If task end time is xx:15, xx:30, xx:45, xx:00 don't take the next cell
    if((end-start) % 15 == 0){
        span = span + 1;
    }else{
        span = span+2;
    }

    // Create new task from values inputted
    Task* task = new Task(taskTitle, taskDesc, ui->dateTimeStart->dateTime(), ui->dateTimeEnd->dateTime(), DURATION_DEFAULT, PRIORITY_DEFAULT, 1);

    emit sendToCalendar(task, m_row, m_column, span);

    task->save("weekly_tasks");

    close();
}

void AddTaskFormWeekly::SetTaskTitle(QString TaskName){
    ui->taskTitle->setText(TaskName);
}

void AddTaskFormWeekly::SetTaskDescription(QString TaskDescription){
    ui->taskDesc->insertPlainText(TaskDescription);
}

void AddTaskFormWeekly::SetTaskStartTime(QDateTime TaskStartTime){
    ui->dateTimeStart->setDateTime(TaskStartTime);
}

void AddTaskFormWeekly::SetTaskEndTime(QDateTime TaskEndTime){
    ui->dateTimeEnd->setDateTime(TaskEndTime);
}


void AddTaskFormWeekly::on_pbDeleteTask_clicked()
{
    emit sendDeleteToCalendar(m_row, m_column);
    close();
}
