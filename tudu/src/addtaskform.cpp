#include "headers/addtaskform.h"
#include "ui_addtaskform.h"

AddTaskForm::AddTaskForm(QWidget *parent, int r, int c) :
    QDialog(parent),
    ui(new Ui::AddTaskForm)
{
    m_tableRow = r;
    m_tableColumn = c;
    std::cout << "R: " << m_tableRow << " C: " << m_tableColumn << std::endl;

    ui->setupUi(this);
}

AddTaskForm::~AddTaskForm()
{
    delete ui;
}
