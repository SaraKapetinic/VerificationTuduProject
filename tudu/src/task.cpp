#include "task.h"

Task::Task(QString taskTitle,
           QString taskDesc,
           QDate startDate,
           QDate endDate,
           QTime startTime,
           QTime endTime,
           int priority)
{
    m_taskTitle = taskTitle;
    m_taskDesc = taskDesc;
    m_startDate = startDate;
    m_endDate = endDate;
    m_startTime = startTime;
    m_endTime = endTime;
    m_priority = priority;
}

QString Task::getTaskTitle(){
    return m_taskTitle;
}

QString Task::getTaskDesc(){
    return m_taskDesc;
}
