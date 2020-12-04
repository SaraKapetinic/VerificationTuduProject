#ifndef ADDTASKFORM_H
#define ADDTASKFORM_H

#include <QDialog>
#include <iostream>

namespace Ui {
class AddTaskForm;
}

class AddTaskForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskForm(QWidget *parent = 0, int row = 0, int column = 0);
    ~AddTaskForm();

private:
    Ui::AddTaskForm *ui;
    int m_tableRow;
    int m_tableColumn;
};

#endif // ADDTASKFORM_H
