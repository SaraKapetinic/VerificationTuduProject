#ifndef ADDTASKFORM_H
#define ADDTASKFORM_H

#include <QDialog>

namespace Ui {
class AddTaskForm;
}

class AddTaskForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskForm(QWidget *parent = 0);
    ~AddTaskForm();

private:
    Ui::AddTaskForm *ui;
};

#endif // ADDTASKFORM_H
