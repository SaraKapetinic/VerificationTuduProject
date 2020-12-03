#include "headers/addtaskform.h"
#include "ui_addtaskform.h"

AddTaskForm::AddTaskForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskForm)
{
    ui->setupUi(this);
}

AddTaskForm::~AddTaskForm()
{
    delete ui;
}
