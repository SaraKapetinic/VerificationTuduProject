#ifndef TUDUTASK_H
#define TUDUTASK_H

#include <QDialog>

namespace Ui {
class TuduTask;
}

class TuduTask : public QDialog
{
    Q_OBJECT

public:
    explicit TuduTask(QWidget *parent = nullptr);
    ~TuduTask();

private:
    Ui::TuduTask *ui;
};

#endif // TUDUTASK_H
