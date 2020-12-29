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

Task::Task(QJsonValue jsonValue) :
        QStandardItem(jsonValue["taskTitle"].toString())
{
    this->name = jsonValue["taskTitle"].toString();
    this->description = jsonValue["taskDescription"].toString();
    this->startTime = QDateTime::fromString(jsonValue["taskStartTime"].toString(), "dd.MM.yyyy. hh:mm");
    this->endTime = QDateTime::fromString(jsonValue["taskEndTime"].toString(), "dd.MM.yyyy. hh:mm");
    this->creationTime = QDateTime();
    this->duration = QTime::fromString(jsonValue["taskDuration"].toString(), "hh:mm");
    this->priority = jsonValue["taskPriority"].toInt();
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
