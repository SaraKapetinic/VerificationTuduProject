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
    item->setName(title);

    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setDragEnabled(true);

    // set the items data to apropriate values
    item->setData(QVariant::fromValue<QString>(title), Qt::UserRole + NAME_ROLE);
    item->setData(QVariant::fromValue<QString>(desc), Qt::UserRole + DESCRIPTION_ROLE);
    item->setData(QVariant::fromValue<int>(priority), Qt::UserRole + PRIORITY_DEFAULT);
    item->setData(QVariant::fromValue<QString>(item->getCreationTimeString()),
                  Qt::UserRole + CREATIONTIME_ROLE);

    static_cast<QStandardItemModel *>(model())->appendRow(item);
    scrollToBottom();
}



