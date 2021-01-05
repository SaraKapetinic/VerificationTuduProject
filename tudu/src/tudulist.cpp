#include "headers/tudulist.h"
#include <QStandardItemModel>
#include "headers/task.h"
#include <iostream>

TuduList::TuduList(QWidget *parent) :
    QListView(parent)
{

    setModel(new QStandardItemModel(this));
}

void TuduList::addTask(const QString &title, const QString desc, const int priority)
{
    auto *item = new Task(title, desc, priority);

    auto pixmap = item->selectIcon(priority);
    item->setIcon(QIcon(pixmap));

    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setDragEnabled(true);
    static_cast<QStandardItemModel *>(model())->appendRow(item);
    scrollToBottom();
}



