#include "headers/addtaskformweekly.h"
#include "ui_addtaskformweekly.h"
#include "ui_mainwindow.h"
#include "headers/init.h"
#include "headers/task.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>


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

void saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    // Open file for appending
    jsonFile.open(QFile::Append);
    // Write data to file
    jsonFile.write(document.toJson());
}

void AddTaskFormWeekly::on_pbSaveTask_clicked()
{
    QString taskTitle = ui->taskTitle->text();
    QString taskDesc = ui->taskDesc->toPlainText();

    int start = ui->dateTimeStart->time().hour() * 60 + ui->dateTimeStart->time().minute();
    int end = ui->dateTimeEnd->time().hour() * 60 + ui->dateTimeEnd->time().minute();
    int span = (end - start)/15;

    emit sendToCalendar(taskTitle, m_row, m_column, span);

    // Create new task from values inputted
    Task* task = new Task(taskTitle, taskDesc, ui->dateTimeStart->dateTime(), ui->dateTimeEnd->dateTime(), DURATION_DEFAULT, PRIORITY_DEFAULT, 1);


    QJsonDocument jsonDocument;
    QJsonObject taskJsonObject;

    // Create JSON key-value pairs
    // TODO code below should be moved to a separate function
    taskJsonObject.insert("taskTitle", task->getName());
    taskJsonObject.insert("taskDescription", task->getDescription());
    taskJsonObject.insert("taskStartTime", task->getStartTime().toString("hh:mm"));
    taskJsonObject.insert("taskEndTime", task->getEndTime().toString("hh:mm"));
    taskJsonObject.insert("taskDuration", task->getDuration().toString());
    taskJsonObject.insert("taskPriority", task->getPriority());

    // Set an object from those k-v pairs
    jsonDocument.setObject(taskJsonObject);

    // Pass path to desktop to save file there
    QString saveLocation = QString("%1/tuduTasks.json").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    saveJson(jsonDocument, saveLocation);


    close();
}
