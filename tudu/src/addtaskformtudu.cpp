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

void AddTaskFormTudu::on_tuduTaskSave_clicked(){
    auto taskTitle = ui->taskTitle->text();
    auto taskDesc = ui->taskDesc->toPlainText();
    auto taskPriority = ui->taskPriority->currentIndex();

    Task* task = new Task(taskTitle,taskDesc,taskPriority);

    emit sendToTuduList(taskTitle, taskDesc, taskPriority);

    task->save("tuduList_tasks");

    close();
}
