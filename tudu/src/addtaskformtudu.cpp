#include "headers/addtaskformtudu.h"
#include "ui_addtaskformtudu.h"

AddTaskFormTudu::AddTaskFormTudu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskFormTudu)
{
    ui->setupUi(this);
}

AddTaskFormTudu::~AddTaskFormTudu()
{
    delete ui;
}
