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

    auto icon = item->fetchIcon(priority);

    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setDragEnabled(true);

    // set the items data to apropriate values
    item->setData(QVariant::fromValue<QString>(title), NAME_ROLE);
    item->setData(QVariant::fromValue<QString>(desc), DESCRIPTION_ROLE);
    item->setData(QVariant::fromValue<int>(priority), PRIORITY_DEFAULT);
    item->setData(QVariant::fromValue<QString>(item->getCreationTimeString()),
                  CREATIONTIME_ROLE);

    item->setIcon(icon);

    static_cast<QStandardItemModel *>(model())->appendRow(item);
    scrollToBottom();

}



