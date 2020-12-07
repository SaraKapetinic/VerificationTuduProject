#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{
public:
    Task(QString taskTitle = "",
         QString taskDesc = "",
         QDate startDate = QDate(0, 0, 0),
         QDate endDate = QDate(0, 0, 0),
         QTime startTime = QTime(0, 0),
         QTime endTime = QTime (0, 0),
         int priority = 0);

    QString getTaskTitle();
    QString getTaskDesc();

private:
    QString m_taskTitle;
    QString m_taskDesc;
    QDate m_startDate;
    QDate m_endDate;
    QTime m_startTime;
    QTime m_endTime;
    int m_priority;

};

#endif // TASK_H
