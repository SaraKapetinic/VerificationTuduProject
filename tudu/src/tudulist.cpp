#include "headers/tudulist.h"
#include <QStandardItemModel>
#include "headers/task.h"
#include <iostream>
#include <QVariant>

TuduList::TuduList(QWidget *parent) :
    QListView(parent)
{

    setModel(new QStandardItemModel(this));
}

void TuduList::addTask(const QString &title, const QString desc, const int priority)
{
    auto *item = new Task(title, desc, priority);

    this->addTask(item);

}

void TuduList::addTask(Task *task){

    auto icon = task->fetchIcon(task->getPriority());

    task->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    task->setDragEnabled(true);

    // set the items data to apropriate values
    task->setData(QVariant::fromValue<QString>(task->getName()), NAME_ROLE);
    task->setData(QVariant::fromValue<QString>(task->getDescription()), DESCRIPTION_ROLE);
    task->setData(QVariant::fromValue<int>(task->getPriority()), PRIORITY_DEFAULT);
    task->setData(QVariant::fromValue<QString>(task->getCreationTimeString()),
                  CREATIONTIME_ROLE);

    task->setIcon(icon);

    static_cast<QStandardItemModel *>(model())->appendRow(task);
    scrollToBottom();
}


