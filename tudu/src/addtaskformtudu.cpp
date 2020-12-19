#include "headers/addtaskformtudu.h"
#include "ui_tudutask.h"

addTaskFormTudu::addTaskFormTudu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TuduTask)
{
    ui->setupUi(this);
}

addTaskFormTudu::~addTaskFormTudu()
{
    delete ui;
}
