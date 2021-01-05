#include "headers/task.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QJsonArray>
#include <QFile>
#include <iostream>


Task::Task(
        QString Tname,
        QString Tdescription,
        QDateTime TstartTime,
        QDateTime TendTime,
        QTime Tduration,
        qint32 Tpriority,
        bool TallDayLong) :
    QStandardItem(Tname)
{
    this->name = Tname;
    this->description = Tdescription;
    this->startTime = TstartTime;
    this->endTime = TendTime;
    this->creationTime = QDateTime::currentDateTime();
    this->duration = Tduration;
    this->priority = Tpriority;
    this->allDayLong = TallDayLong;
}

Task::Task(QJsonValue jsonValue) :
        QStandardItem(jsonValue["title"].toString())
{
    this->name = jsonValue["title"].toString();
    this->description = jsonValue["description"].toString();
    this->startTime = QDateTime::fromString(jsonValue["startTime"].toString(), START_END_TIME_FORMAT);
    this->endTime = QDateTime::fromString(jsonValue["endTime"].toString(), START_END_TIME_FORMAT);
    this->creationTime = QDateTime::fromString(jsonValue["creationTime"].toString(), CREATION_TIME_FORMAT);
    this->duration = QTime::fromString(jsonValue["duration"].toString(), "hh:mm");
    this->priority = jsonValue["priority"].toInt();
    this->allDayLong = 1;
}

Task::Task(
    QString Tname,
    QString Tdescription,
    qint32 Tpriority
           ) :
    QStandardItem(Tname)
{
    this->name = Tname;
    this->description = Tdescription;
    this->priority = Tpriority;
    this->startTime = STARTTIME_DEFAULT;
    this->endTime = ENDTIME_DEFAULT;
    this->creationTime = QDateTime::currentDateTime();
    this->duration = DURATION_DEFAULT;
    this->allDayLong = ALLDAYLONG_DEFAULT;
}

Task::Task(Task &obj) :
    QStandardItem(obj.name)
{
    this->name = obj.name;
    this->description = obj.description;
    this->startTime = obj.startTime;
    this->endTime = obj.endTime;
    // TODO should we copy the creation time?
    this->creationTime = obj.creationTime;
    this->duration = obj.duration;
    this->priority = obj.priority;
    this->allDayLong = obj.allDayLong;
}

Task::~Task()
{

}

QString Task::getName() const
{
    return name;
}

void Task::setName(const QString &value)
{
    name = value;
}

QString Task::getDescription() const
{
    return description;
}

void Task::setDescription(const QString &value)
{
    description = value;
}

QDateTime Task::getStartTime() const
{
    return startTime;
}

void Task::setStartTime(const QDateTime &value)
{
    startTime = value;
}

QDateTime Task::getEndTime() const
{
    return endTime;
}

void Task::setEndTime(const QDateTime &value)
{
    endTime = value;
}

QDateTime Task::getCreationTime() const
{
    return creationTime;
}

QString Task::getCreationTimeString() const
{
    return creationTime.toString(CREATION_TIME_FORMAT);
}

QTime Task::getDuration() const
{
    return duration;
}

void Task::setDuration(const QTime &value)
{
    duration = value;
}

qint32 Task::getPriority() const
{
    return priority;
}

void Task::setPriority(const qint32 &value)
{
    priority = value;
}

void Task::save(QString fileName) {

    // TODO add a check if the file name is valid

    QString saveLocation = QString("%1/%2.json")
            .arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), fileName);
    std::cout<<saveLocation.toStdString();
    QFile file(saveLocation);
    file.open(QIODevice::ReadOnly);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    file.close();

    auto creationTime = this->getCreationTimeString();
    auto data =
            QJsonObject ({
               qMakePair(QString("title"),  QJsonValue(this->getName())),
               qMakePair(QString("description"),  QJsonValue(this->getDescription())),
               qMakePair(QString("startTime"),  QJsonValue(this->getStartTime().toString(START_END_TIME_FORMAT))),
               qMakePair(QString("endTime"),  QJsonValue(this->getEndTime().toString(START_END_TIME_FORMAT))),
               qMakePair(QString("creationTime"),  QJsonValue(creationTime)),
               qMakePair(QString("duraton"),  QJsonValue(this->getDuration().toString())),
               qMakePair(QString("priority"),  QJsonValue(this->getPriority())),
            });

    auto jsonArray = jsonDocument.object();
    jsonArray.insert(creationTime, data);

    QJsonDocument final_doc(jsonArray);
    file.open(QIODevice::WriteOnly);
    file.write(final_doc.toJson());
    file.close();
}
