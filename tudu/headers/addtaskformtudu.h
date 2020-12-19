#ifndef TUDUTASK_H
#define TUDUTASK_H

#include <QDialog>

namespace Ui {
class TuduTask;
}

class addTaskFormTudu : public QDialog
{
    Q_OBJECT

public:
    explicit addTaskFormTudu(QWidget *parent = nullptr);
    ~addTaskFormTudu();

private:
    Ui::TuduTask *ui;
};

#endif // TUDUTASK_H
