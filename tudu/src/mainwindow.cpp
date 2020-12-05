#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QColorDialog>
#include <iostream>
#include <QTextEdit>
#include <regex>
#include <QRegularExpression>
#include "headers/addtaskform.h"

#define NUM_OF_WEEKDAYS 7
#define HOURS_IN_DAY 24
#define MINUTES_IN_HOUR 60
#define MINUTE_INCREMENTS 15


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate currentDate = ui->calendarMonths->selectedDate();

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = currentDate.dayOfWeek();

    // Number of days till the end of the week
    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;

    QVector<int> daysAdded(NUM_OF_WEEKDAYS);
    for (int i=NUM_OF_WEEKDAYS-1; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }

    QStringList days = {"Monday\n", "Tuesday\n", "Wednesday\n", "Thursday\n",
                        "Friday\n", "Saturday\n", "Sunday\n"};

    // Make header text Day\n Date
    for(int i=0; i<days.size(); i++){
        days[i].append(currentDate.addDays(daysAdded[i]).toString("dd.MM.yyyy."));
    }

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels(days);

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


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    AddTaskForm mDialog(this, row, column);
    mDialog.setModal(true);
    mDialog.exec();

    /*
    // Window that pops up on double click
    QWidget *taskWindow = new QWidget();

    // Set window title
    taskWindow->setWindowTitle("Add New Task");

    // Set collected time and date
    QLabel *lDate = new QLabel();
    lDate->setText("Date:\n" + date);

    QLabel *lTime = new QLabel();
    lTime->setText("Time:\n" + time);


    // Field for describing a task
    QTextEdit* taskTudu = new QTextEdit();
    taskTudu->setPlaceholderText("Task description");
    taskTudu->setMinimumHeight(50);
    taskTudu->setMaximumHeight(50);


    // Button for adding a task
    QPushButton* addTaskButton = new QPushButton();
    addTaskButton->setText("Add Task");

    // Layout configuration
    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lDate);
    layout->addWidget(lTime);
    layout->addWidget(taskTudu);
    layout->addWidget(addTaskButton);

    layout->setContentsMargins(150, 200, 150, 200);

    taskWindow->setLayout(layout);

    taskWindow->show();*/
}
