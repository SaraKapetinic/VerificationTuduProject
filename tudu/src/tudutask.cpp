#include "headers/tudutask.h"
#include "ui_tudutask.h"

TuduTask::TuduTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TuduTask)
{
    ui->setupUi(this);
}

TuduTask::~TuduTask()
{
    delete ui;
}
