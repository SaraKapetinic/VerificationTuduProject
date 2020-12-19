#include "headers/task.h"


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




