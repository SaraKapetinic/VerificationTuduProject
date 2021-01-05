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

QList<QDate> currentWeek;
QDate today = QDate::currentDate();

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
    WeeklyView *week = new WeeklyView(ui);
    week->execute();

    // Append to list so we can use it in cellDoubleClicked
    currentWeek.append(week->getCurrentWeek());


    auto size = new QSize(0,0);
    ui->tableWidget->setIconSize(*size);

}

void MainWindow::recieveInTuduList(QString title, QString desc, int priority){
    ui->scrollAreaWidgetContents_2->findChildren<TuduList*>()[0]->addTask(title, desc, priority);
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
    QColor taskColor = QColor(0, 204, 204);
    item->setBackground(taskColor);
    ui->tableWidget->setItem(row, column, item);
    ui->tableWidget->setSpan(row, column, span, 1);

}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{

    QTime time = QTime::fromString(ui->tableWidget->verticalHeaderItem(row)->text(), "hh:mm");
    QDate date = currentWeek[column];

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
    mDialog->setModal(true);
    mDialog->exec();

}

void MainWindow::on_calendarMonths_activated(const QDate &date)
{

    WeeklyView* week = new WeeklyView(ui, date);
    week->execute();

    ui->tabWidget->setCurrentWidget(ui->tabWeekTest);


}
