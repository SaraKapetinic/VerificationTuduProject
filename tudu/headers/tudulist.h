#ifndef TUDULIST_H
#define TUDULIST_H

#include <QListView>

class TuduList : public QListView
{
    Q_OBJECT
public:
    explicit TuduList(QWidget *parent = nullptr);
public slots:
    void addTask(const QString &text);
};

#endif // TUDULIST_H
