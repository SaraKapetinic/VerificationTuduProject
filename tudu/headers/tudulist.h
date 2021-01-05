#ifndef TUDULIST_H
#define TUDULIST_H

#include <QListView>
#include <headers/task.h>

class TuduList : public QListView
{
    Q_OBJECT
public:
    explicit TuduList(QWidget *parent = nullptr);
public slots:
    void addTask(const QString &title, const QString desc, const int priority);
    void addTask(Task *task);
};

#endif // TUDULIST_H
