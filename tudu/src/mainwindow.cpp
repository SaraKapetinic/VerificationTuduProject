#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/addtaskformweekly.h"
#include "headers/tudulist.h"
#include "headers/addtaskformtudu.h"
#include "headers/init.h"
#include <QTextEdit>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QDir>

QList<QDate> currentWeek;

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
    Init *init = new Init();

    // Methods to set up mainwindow
    init->setDays(ui);
    init->setHeaders(ui);

    // Make table fill entire widget
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Append to list so we can use it in cellDoubleClicked
    for(int i=0;i<NUM_OF_WEEKDAYS;i++){
        currentWeek.append(init->getCurrentWeek()[i]);
    }


    // Load from file
    // TODO move the code below (up to 75ish) to the weekly table class

    // TODO load the file location using a macro from task.cpp
    QString fileLocation = QString("%1/weekly_tasks.json")
            .arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    // Open file for reading
    QFile file(fileLocation);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read JSON
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    file.close();
    // Get array so we can see number of tasks in file
    auto savedTasks = jsonDocument.object();

    // Put tasks from file to Weekly table
    if(savedTasks.size() != 0){
        auto model = ui->tableWidget->model();
        foreach(const QString& key, savedTasks.keys()){
            // TODO add a check to see if the task is in the current week
            // if (isCurrentWeem(key)) or something like that
            auto currentTask = new Task(savedTasks.value(key));
            auto taskColumn = currentTask->getStartTime().date().dayOfWeek() - 1;
            auto task_row = currentTask->getStartTime().time().msecsSinceStartOfDay() / (1000 * 60 * 15);

            // TODO send a task object to the cell in our table
            model->setData(model->index(task_row, taskColumn),currentTask->getName());
        }
    }else{
        std::cerr << "No tasks in file" << std::endl;
    }

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
        std::cout << item->data(NAME_ROLE).toString().toStdString() << std::endl;
        mDialog->SetTaskTitle(item->data(NAME_ROLE).toString());
    }

    // Send data from form to main window
    connect(mDialog,SIGNAL(sendToCalendar(Task*, int, int, int)),
            this, SLOT(recieveFromTask(Task*, int, int, int)));
    mDialog->setModal(true);
    mDialog->exec();

}

