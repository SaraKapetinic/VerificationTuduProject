#ifndef ADDTASKFORMTUDU_H
#define ADDTASKFORMTUDU_H

#include <QDialog>

namespace Ui {
class AddTaskFormTudu;
}

class AddTaskFormTudu : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskFormTudu(QWidget *parent = nullptr);
    ~AddTaskFormTudu();

private:
    Ui::AddTaskFormTudu *ui;
};

#endif // ADDTASKFORMTUDU_H
