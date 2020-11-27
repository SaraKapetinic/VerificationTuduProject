#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QColorDialog>
#include <iostream>
#include <QTextEdit>
#include <regex>
#include <QRegularExpression>

#define NUM_OF_WEEKDAYS 7

// Function to return children of parent widget based on search regex
QList<QTextEdit *> widgets(QWidget* parent, QString search)
{
    QRegularExpression exp(search);
    return parent->findChildren<QTextEdit *>(exp);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate currentDate = ui->calendarMonths->selectedDate();
    QString dayNames[] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    int currentDayOfWeek = currentDate.dayOfWeek();

    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;
    QVector<int> daysAdded(8);
    for (int i=7; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }

    QWidget* tabWeekWidget = ui->tabWeek;
    // Getting children of tabWeekWidget
    auto children = widgets(tabWeekWidget, "day");

    for (auto i=0;i<children.size();i++) {
        // Aligning to center
        children[i]->setAlignment(Qt::AlignCenter);

        // Adding a day name labels
        children[i]->insertPlainText(dayNames[i]);

        // Adding date to corresponding day
        children[i]->append(currentDate.addDays(daysAdded[i+1]).toString("dd.MM.yyyy."));

        // Highlight current day
        if(currentDayOfWeek == i+1){
            children[i]->setStyleSheet("background-color: rgba(0, 0, 0, 0.15)");
        }
    }
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
