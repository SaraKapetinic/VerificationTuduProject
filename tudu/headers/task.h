#ifndef TASK_H
#define TASK_H

#include <QStandardItem>
#include <QDateTime>
#include <QTime>


class Task : public QStandardItem
{
public:
    Task(const QString &text);
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
