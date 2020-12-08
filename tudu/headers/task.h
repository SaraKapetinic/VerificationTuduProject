#ifndef TASK_H
#define TASK_H

#include <QStandardItem>
#include <QDateTime>
#include <QTime>


class Task : public QStandardItem
{
public:
    Task();

    Task(QString Tname,QString Tdescription,QDateTime TstartTime,QDateTime TendTime,QTime Tduration,qint32 Tpriority,bool TallDayLong);

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

    QTime getDuration() const;
    void setDuration(const QTime &value);

    qint32 getPriority() const;
    void setPriority(const qint32 &value);

protected:
    QString name;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
    QTime duration;
    qint32 priority;
    bool allDayLong;
};

#endif // TASK_H
