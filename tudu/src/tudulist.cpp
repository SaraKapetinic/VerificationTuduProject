#include "headers/tudulist.h"
#include <QStandardItemModel>
#include "headers/task.h"
#include <iostream>

TuduList::TuduList(QWidget *parent) :
    QListView(parent)
{

    setModel(new QStandardItemModel(this));
}

void TuduList::addTask(const QString &text)
{
    auto *item = new Task(text);
    item->setName(text);

    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setDragEnabled(true);

    static_cast<QStandardItemModel *>(model())->appendRow(item);
    scrollToBottom();
    }



