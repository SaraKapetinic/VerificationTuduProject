#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QColorDialog>
#include <iostream>
#include <QTextEdit>

#define NUM_OF_WEEKDAYS 7


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QDate currentDate = ui->calendarMonths->selectedDate();

    ui->day_1->setStyleSheet("background-color: rgba(0,0,0, 0.15);");
//    TODO: change bg color of the current day

    ui->day_1->setAlignment(Qt::AlignCenter);
    ui->day_2->setAlignment(Qt::AlignCenter);
    ui->day_3->setAlignment(Qt::AlignCenter);
    ui->day_4->setAlignment(Qt::AlignCenter);
    ui->day_5->setAlignment(Qt::AlignCenter);
    ui->day_6->setAlignment(Qt::AlignCenter);
    ui->day_7->setAlignment(Qt::AlignCenter);

    // Adding a day name labels
    ui->day_1->insertPlainText("Monday");
    ui->day_2->insertPlainText("Tuesday");
    ui->day_3->insertPlainText("Wednesday");
    ui->day_4->insertPlainText("Thursday");
    ui->day_5->insertPlainText("Friday");
    ui->day_6->insertPlainText("Saturday");
    ui->day_7->insertPlainText("Sunday");

    int currentDayOfWeek = currentDate.dayOfWeek();
    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;
    QVector<int> daysAdded(8);
    for (int i=7; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }

    ui->day_1->append(currentDate.addDays(daysAdded[1]).toString("dd.MM.yyyy."));
    ui->day_2->append(currentDate.addDays(daysAdded[2]).toString("dd.MM.yyyy."));
    ui->day_3->append(currentDate.addDays(daysAdded[3]).toString("dd.MM.yyyy."));
    ui->day_4->append(currentDate.addDays(daysAdded[4]).toString("dd.MM.yyyy."));
    ui->day_5->append(currentDate.addDays(daysAdded[5]).toString("dd.MM.yyyy."));
    ui->day_6->append(currentDate.addDays(daysAdded[6]).toString("dd.MM.yyyy."));
    ui->day_7->append(currentDate.addDays(daysAdded[7]).toString("dd.MM.yyyy."));
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
