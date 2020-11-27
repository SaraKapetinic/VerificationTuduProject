#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QColorDialog>
#include <iostream>
#include <QTextEdit>
#include <regex>
#include <QRegularExpression>

#define NUM_OF_WEEKDAYS 7

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate currentDate = ui->calendarMonths->selectedDate();

    int currentDayOfWeek = currentDate.dayOfWeek();

    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;
    QVector<int> daysAdded(8);
    for (int i=7; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }

    QStringList days = {"Monday\n", "Tuesday\n", "Wednesday\n", "Thursday\n", "Friday\n", "Saturday\n", "Sunday\n"};

    // Make header text Day\n Date
    for(int i = 0;i<days.size();i++){
        days[i].append(currentDate.addDays(daysAdded[i+1]).toString("dd.MM.yyyy."));
    }

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels(days);

    // Set row headers
    ui->tableWidget->setVerticalHeaderLabels(
                {"07.00", "08.00", "09.00", "10.00", "11.00", "12.00", "13.00", "14.00", "15.00", "16.00", "17.00", "18.00", "19.00", "20.00", "21.00", "22.00", "23.00"}
                );

    // Make table fill entire widget
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Example of text in particular cell (TODO)
    ui->tableWidget->setItem(1,1, new QTableWidgetItem("Tekst iz taska"));

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
