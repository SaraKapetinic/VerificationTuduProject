#ifndef TASK_H
#define TASK_H

#define DESCRIPTION_DEFAULT ("")
#define STARTTIME_DEFAULT (QDateTime::currentDateTime())
#define ENDTIME_DEFAULT (QDateTime::currentDateTime())
#define DURATION_DEFAULT (QTime::currentTime())
#define PRIORITY_DEFAULT (1)
#define ALLDAYLONG_DEFAULT (false)


#include <QStandardItem>
#include <QDateTime>
#include <QTime>


class Task : public QStandardItem
{
public:

    Task(QString Tname, QString Tdescription = DESCRIPTION_DEFAULT , QDateTime TstartTime = STARTTIME_DEFAULT, QDateTime TendTime = ENDTIME_DEFAULT, QTime Tduration = DURATION_DEFAULT, qint32 Tpriority = PRIORITY_DEFAULT, bool TallDayLong = ALLDAYLONG_DEFAULT);

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

    QTime getDuration() const;
    void setDuration(const QTime &value);

    qint32 getPriority() const;
    void setPriority(const qint32 &value);

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
