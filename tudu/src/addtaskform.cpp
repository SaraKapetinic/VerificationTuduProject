#include "headers/addtaskform.h"
#include "ui_addtaskform.h"

AddTaskForm::AddTaskForm(QWidget *parent, int row, int column) :
    QDialog(parent),
    ui(new Ui::AddTaskForm)
{
    m_tableRow = row;
    m_tableColumn = column;

    ui->setupUi(this);
}

AddTaskForm::~AddTaskForm()
{
    delete ui;
}
