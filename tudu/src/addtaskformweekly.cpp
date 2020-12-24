#include "headers/addtaskformweekly.h"
#include "ui_addtaskformweekly.h"
#include "ui_mainwindow.h"
#include "headers/init.h"
#include "headers/task.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
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

void save(Task* task) {
    QString saveLocation = QString("%1/tuduTasks.json").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    QFile file(saveLocation);
    file.open(QIODevice::ReadOnly);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    file.close();

    auto taskData =
            QJsonObject ({
               qMakePair(QString("taskTitle"),  QJsonValue(task->getName())),
               qMakePair(QString("taskDescription"),  QJsonValue(task->getDescription())),
               qMakePair(QString("taskStartTime"),  QJsonValue(task->getStartTime().toString("dd.MM.yyyy. hh:mm"))),
               qMakePair(QString("taskEndTime"),  QJsonValue(task->getEndTime().toString("dd.MM.yyyy. hh:mm"))),
               qMakePair(QString("taskDuraton"),  QJsonValue(task->getDuration().toString())),
               qMakePair(QString("taskPriority"),  QJsonValue(task->getPriority())),
            });

    QJsonArray jsonArray = jsonDocument.array();
    jsonArray.push_back(taskData);


    QJsonDocument final_doc(jsonArray);
    file.open(QIODevice::WriteOnly);
    file.write(final_doc.toJson());
    file.close();
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

    save(task);

    close();
}
