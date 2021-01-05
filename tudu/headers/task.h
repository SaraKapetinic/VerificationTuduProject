#ifndef TASK_H
#define TASK_H

#define DESCRIPTION_DEFAULT ("")
#define STARTTIME_DEFAULT (QDateTime::currentDateTime())
#define ENDTIME_DEFAULT (QDateTime::currentDateTime())
#define DURATION_DEFAULT (QTime::currentTime())
#define PRIORITY_DEFAULT (1)
#define ALLDAYLONG_DEFAULT (false)

#define START_END_TIME_FORMAT "dd.MM.yyyy. hh:mm"
#define CREATION_TIME_FORMAT "dd.MM.yyyy.hh:mm:ms"

#define NAME_ROLE (Qt::UserRole + 1)
#define DESCRIPTION_ROLE (Qt::UserRole + 2)
#define STARTTIME_ROLE (Qt::UserRole + 3)
#define ENDTIME_ROLE (Qt::UserRole + 4)
#define DURATION_ROLE (Qt::UserRole + 5)
#define PRIORITY_ROLE (Qt::UserRole + 6)
#define CREATIONTIME_ROLE (Qt::UserRole + 7)

#include <QStandardItem>
#include <QDateTime>
#include <QTime>
#include <QJsonValue>

class Task : public QStandardItem
{
public:

    Task(QString Tname,
        QString Tdescription = DESCRIPTION_DEFAULT,
        QDateTime TstartTime = STARTTIME_DEFAULT,
        QDateTime TendTime = ENDTIME_DEFAULT,
        QTime Tduration = DURATION_DEFAULT,
        qint32 Tpriority = PRIORITY_DEFAULT,
        bool TallDayLong = ALLDAYLONG_DEFAULT
        );

    Task(QString Tname,
        QString Tdescription,
        qint32 Tpriority
        );

    Task(QJsonValue jsonValue);

    Task(Task &obj);

    ~Task();

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QDateTime getStartTime() const;
    void setStartTime(const QDateTime &value);

    QDateTime getEndTime() const;
    void setEndTime(const QDateTime &value);

    QDateTime getCreationTime() const;
    QString getCreationTimeString() const;

    QTime getDuration() const;
    void setDuration(const QTime &value);

    qint32 getPriority() const;
    void setPriority(const qint32 &value);

    void save(QString fileName);

protected:
    QString name;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
    QDateTime creationTime;
    QTime duration;
    qint32 priority;
    bool allDayLong;
};

#endif // TASK_H
