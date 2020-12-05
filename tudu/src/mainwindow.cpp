#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QColorDialog>
#include <iostream>
#include <QTextEdit>
#include <regex>
#include <QColor>
#include <QRegularExpression>
#include "headers/addtaskform.h"

#define NUM_OF_WEEKDAYS 7
#define HOURS_IN_DAY 24
#define MINUTES_IN_HOUR 60
#define MINUTE_INCREMENTS 15

QList<QDate> currentWeek;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate currentDate = ui->calendarMonths->selectedDate();

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = currentDate.dayOfWeek();

    // Highlight current day header
    QColor headerColor = (255);
    ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setBackground(headerColor);

    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;

    QVector<int> daysAdded(NUM_OF_WEEKDAYS);
    for (int i=NUM_OF_WEEKDAYS-1; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }


    // Fill list currentWeek and make header text
    QStringList horizontalHeaders;
    for(int i = 0;i<7;i++){
        currentWeek.append(currentDate.addDays(daysAdded[i]));
        horizontalHeaders.append(ui->tableWidget->horizontalHeaderItem(i)->text().append(currentDate.addDays(daysAdded[i]).toString("\ndd.MM.yyyy.")));
    }

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeaders);

    // Set row headers
    QStringList verticalHeaders;
    QString time;
    for (int i=0; i<HOURS_IN_DAY; i++) {
        for (int j=0; j<MINUTES_IN_HOUR; j+=MINUTE_INCREMENTS) {
            time = "";
            time.sprintf("%02d.%02d", i, j);
            verticalHeaders << time;
        }
    }
    ui->tableWidget->setVerticalHeaderLabels(verticalHeaders);

    // Make table fill entire widget
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::on_addTaskButtonClicked()
{
    printf("Adding a new task to TUDU\n");
    QTextEdit *frame = new QTextEdit();
    frame->setPlaceholderText("Add task description");
    frame->placeholderText();
    frame->setMinimumHeight(20);
    frame->setMaximumHeight(100);

    ui->verticalLayoutTUDU->addWidget(frame,Qt::AlignTop);
    // do other init stuff

//    AddTaskForm mDialog;
//    mDialog.setModal(true);
//    mDialog.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieveFromTask(QString text, int row, int column){
    auto model = ui->tableWidget->model();
    model->setData(model->index(row, column), text);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QTime time = QTime::fromString(ui->tableWidget->verticalHeaderItem(row)->text(), "hh.mm");
    QDate date = currentWeek[column];

    AddTaskForm *mDialog = new AddTaskForm(this, time, date, row, column);

    // Send data from form to main window
    connect(mDialog, SIGNAL(sendToCalendar(QString, int, int)), this, SLOT(recieveFromTask(QString, int, int)));
    mDialog->setModal(true);
    mDialog->exec();

}
