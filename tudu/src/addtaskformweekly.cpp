#include "headers/addtaskformweekly.h"
#include "ui_addtaskformweekly.h"
#include "ui_mainwindow.h"
#include "headers/init.h"
#include "headers/task.h"
#include <QtXml>
#include <QJsonDocument>
#include <QJsonArray>

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
    ui->startDate->setDate(m_date);
    ui->startTime->setTime(m_time);


    ui->dateTimeStart->setDate(m_date);
    ui->dateTimeStart->setTime(m_time);


    // Suppose it's a one-day task
    ui->endDate->setDate(m_date);
    ui->dateTimeEnd->setDate(m_date);

    // By deafult set end time +15min from start time
    ui->endTime->setTime(m_time.addSecs(15*SECONDS_IN_MINUTE));
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

    int start = ui->startTime->time().hour() * 60 + ui->startTime->time().minute();
    int end = ui->endTime->time().hour() * 60 + ui->endTime->time().minute();
    int span = (end - start)/15;

    emit sendToCalendar(taskTitle, m_row, m_column, span);

    // Create new task from values inputted
    Task* t = new Task(taskTitle, taskDesc, ui->dateTimeStart->dateTime(), ui->dateTimeEnd->dateTime(), DURATION_DEFAULT, PRIORITY_DEFAULT, 1);


    QJsonDocument jsonDoc;
    QJsonObject taskObject;

    // Create JSON key-value pairs
    taskObject.insert("taskTitle", t->getName());
    taskObject.insert("taskDescription", t->getDescription());
    taskObject.insert("taskStartTime", t->getStartTime().toString("hh:mm"));
    taskObject.insert("taskEndTime", t->getEndTime().toString("hh:mm"));
    taskObject.insert("taskDuration", t->getDuration().toString());
    taskObject.insert("taskPriority", t->getPriority());


    // Set an object from those k-v pairs
    jsonDoc.setObject(taskObject);

    // Pass path to desktop to save file there
    QString saveLocation = QString("%1/saveData.json").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    saveJson(jsonDoc, saveLocation);


    close();
}
