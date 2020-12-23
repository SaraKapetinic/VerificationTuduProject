#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/addtaskformweekly.h"
#include "headers/tudulist.h"
#include "headers/addtaskformtudu.h"
#include "headers/init.h"
#include <QTextEdit>

QList<QDate> currentWeek;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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




    auto tuduList = new TuduList(this);

    tuduList->setDragEnabled(true);
    tuduList->setAcceptDrops(true);
    tuduList->setDropIndicatorShown(true);
    tuduList->setDefaultDropAction(Qt::MoveAction);

    ui->verticalLayoutTUDU->addWidget(tuduList);

}

void MainWindow::recieveInTuduList(QString title, QString desc, int priority){
    auto svi = ui->scrollAreaWidgetContents_2->findChildren<TuduList*>();
    // TODO find a better way to do this (i.e. use findChild method)
    foreach (auto obj, svi) {
        obj->addTask(title, desc, priority);
    }
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

void MainWindow::recieveFromTask(QString text, int row, int column, int span){

    // Show taskTitle in daily view
    auto model = ui->tableWidget->model();
    model->setData(model->index(row, column), text);

    // Make current cell uneditable
    QTableWidgetItem* item = ui->tableWidget->item(row, column);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);

    // Set color of scheduled task
    QColor taskColor = QColor(0, 204, 204);
    item->setBackground(taskColor);
    ui->tableWidget->setSpan(row, column, span, 1);

}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{

    QTime time = QTime::fromString(ui->tableWidget->verticalHeaderItem(row)->text(), "hh:mm");
    QDate date = currentWeek[column];

    AddTaskFormWeekly *mDialog = new AddTaskFormWeekly(this, time, date, row, column);

    // Send data from form to main window
    connect(mDialog, SIGNAL(sendToCalendar(QString, int, int, int)), this, SLOT(recieveFromTask(QString, int, int, int)));
    mDialog->setModal(true);
    mDialog->exec();

}
