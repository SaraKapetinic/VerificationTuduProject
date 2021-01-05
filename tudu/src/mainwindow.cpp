#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/addtaskformweekly.h"
#include "headers/tudulist.h"
#include "headers/addtaskformtudu.h"
#include "headers/weeklyview.h"
#include <QTextEdit>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QDir>
#include <headers/mainwindow.h>

QList<QDate> currentWeek;
QDate today = QDate::currentDate();
WeeklyView* week;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO maybe move this check to main.cpp
    if (!QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).exists()){
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    }

    // Initialization class
    week = new WeeklyView(ui);
    week->execute();

    auto size = new QSize(0,0);
    ui->tableWidget->setIconSize(*size);

    loadTuduFromJson();

}

void MainWindow::recieveInTuduList(QString title, QString desc, int priority){
    ui->scrollAreaWidgetContents_2->findChildren<TuduList*>()[0]->addTask(title, desc, priority);
}
void MainWindow::loadTuduFromJson(){

    QString path = "%1/tuduList_tasks.json";

    QString fileLocation = path.arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    QFile file(fileLocation);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());

    auto savedTasks = jsonDocument.object();

    if(savedTasks.size() != 0){
        foreach(const QString& key, savedTasks.keys()){
            auto currentTask = new Task(savedTasks.value(key));
            ui->scrollAreaWidgetContents_2->findChildren<TuduList*>()[0]->addTask(currentTask);
        }
    }else{
        std::cerr << "No tasks in file" << std::endl;
    }
    file.close();
}

void MainWindow::on_addTaskButtonClicked()
{
//    qDebug("Adding a new task to TUDU");
    AddTaskFormTudu *tDialog = new AddTaskFormTudu(this);
    connect(tDialog, SIGNAL(sendToTuduList(QString, QString, int)), this, SLOT(recieveInTuduList(QString, QString, int)));
    tDialog->setModal(true);
    tDialog->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieveFromTask(Task* task, int row, int column, int span){

    // Show taskTitle in daily view
//    auto model = ui->tableWidget->model();
//    model->setData(model->index(row, column), task->getName());

    auto item = new QTableWidgetItem();

    // Make current cell uneditable
//    QTableWidgetItem* item = ui->tableWidget->item(row, column);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setData(NAME_ROLE, QVariant::fromValue<QString>(task->getName()));
    item->setData(ENDTIME_ROLE, QVariant::fromValue<QDateTime>(task->getEndTime()));
    item->setData(DESCRIPTION_ROLE, QVariant::fromValue<QString>(task->getDescription()));
    item->setData(CREATIONTIME_ROLE,QVariant::fromValue<QString>(task->getCreationTimeString()));
    item->setText(task->getName());

    // Set color of scheduled task
    QColor taskColor = QColor(239, 138, 23);
    item->setBackground(taskColor);
    item->setTextAlignment(Qt::AlignCenter);
    QFont font;
    font.setFamily("Ubuntu");
    font.setPointSize(12);
    item->setFont(font);
    ui->tableWidget->setItem(row, column, item);
    ui->tableWidget->setSpan(row, column, span, 1);

}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{

    QTime time = QTime::fromString(ui->tableWidget->verticalHeaderItem(row)->text(), "hh:mm");
    QDate date = week->getCurrentWeek().at(column);

    AddTaskFormWeekly *mDialog = new AddTaskFormWeekly(this, time, date, row, column);
    mDialog->setWindowTitle("Add New Task");

    auto item = ui->tableWidget->item(row, column);
    if (item){        
        mDialog->SetTaskTitle(item->data(NAME_ROLE).toString());
        mDialog->SetTaskEndTime(item->data(ENDTIME_ROLE).toDateTime());
        mDialog->SetTaskDescription(item->data(DESCRIPTION_ROLE).toString());
    }

    // Send data from form to main window
    connect(mDialog,SIGNAL(sendToCalendar(Task*, int, int, int)),
            this, SLOT(recieveFromTask(Task*, int, int, int)));
    connect(mDialog,SIGNAL(sendDeleteToCalendar(int, int)),
            this, SLOT(recieveDeleteFromTask(int, int)));
    mDialog->setModal(true);
    mDialog->exec();

}
void MainWindow::recieveDeleteFromTask(int row, int column){
    auto item = ui->tableWidget->takeItem(row, column);    
    if(item != nullptr){
        QString fileLocation = QString("%1/weekly_tasks.json")
                .arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

        // Open file for reading
        QFile file(fileLocation);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        // Read JSON
        QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
        file.close();

        auto savedTasks = jsonDocument.object();

        savedTasks.remove(item->data(CREATIONTIME_ROLE).toString());
        delete item;
        ui->tableWidget->setSpan(row,column,1,1);

        QJsonDocument jsonWriteDocument;
        jsonWriteDocument.setObject(savedTasks);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(jsonWriteDocument.toJson());
        file.close();
    }
}

void MainWindow::on_calendarMonths_activated(const QDate &date)
{
//    week->saveTasksToJson();
    week = new WeeklyView(ui, date);
    week->execute();

    ui->tabWidget->setCurrentWidget(ui->tabWeekTest);

}

void removeFromJson(QString id, QString fileName){
    QString fileLocation = QString("%1/%2.json")
            .arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).arg(fileName);

    // Open file for reading
    QFile file(fileLocation);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read JSON
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    file.close();

    auto savedTasks = jsonDocument.object();

    savedTasks.remove(id);
    QJsonDocument jsonWriteDocument;
    jsonWriteDocument.setObject(savedTasks);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(jsonWriteDocument.toJson());
    file.close();
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    AddTaskFormTudu *tDialog = new AddTaskFormTudu(this);
    tDialog->setWindowTitle("Update Task");

    tDialog->setTitle(index.data(NAME_ROLE).toString());
    tDialog->setDescription(index.data(DESCRIPTION_ROLE).toString());
    tDialog->setPriority(index.data(PRIORITY_ROLE).toInt());

    connect(tDialog, SIGNAL(sendToTuduList(QString, QString, int)),
            this, SLOT(recieveInTuduList(QString, QString, int)));

    removeFromJson(index.data(CREATIONTIME_ROLE).toString(), QString("tuduList_tasks"));
    // TODO Edit task insted of removing it...
    ui->scrollAreaWidgetContents_2->findChildren<TuduList*>()[0]->model()->removeRow(index.row());
    tDialog->setModal(true);
    tDialog->exec();
}
