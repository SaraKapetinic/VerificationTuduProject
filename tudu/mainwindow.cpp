#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QColorDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QDate currentDate = ui->calendarMonths->selectedDate();

    ui->teMonday->setStyleSheet("background-color: rgba(0,0,0, 0.15);");

    ui->teMonday->setAlignment(Qt::AlignCenter);
    ui->teTuesday->setAlignment(Qt::AlignCenter);
    ui->teWednesday->setAlignment(Qt::AlignCenter);
    ui->teThursday->setAlignment(Qt::AlignCenter);
    ui->teFriday->setAlignment(Qt::AlignCenter);
    ui->teSaturday->setAlignment(Qt::AlignCenter);
    ui->teSunday->setAlignment(Qt::AlignCenter);

    ui->teMonday->insertPlainText("Monday");
    ui->teTuesday->insertPlainText("Tuesday");
    ui->teWednesday->insertPlainText("Wednesday");
    ui->teThursday->insertPlainText("Thursday");
    ui->teFriday->insertPlainText("Friday");
    ui->teSaturday->insertPlainText("Saturday");
    ui->teSunday->insertPlainText("Sunday");


    ui->teMonday->append(currentDate.toString("dd.MM.yyyy."));
    ui->teTuesday->append(currentDate.addDays(1).toString("dd.MM.yy."));
    ui->teWednesday->append(currentDate.addDays(2).toString("dd.MM.yy."));
    ui->teThursday->append(currentDate.addDays(3).toString("dd.MM.yy."));
    ui->teFriday->append(currentDate.addDays(4).toString("dd.MM.yy."));
    ui->teSaturday->append(currentDate.addDays(5).toString("dd.MM.yy."));
    ui->teSunday->append(currentDate.addDays(6).toString("dd.MM.yy."));



}

MainWindow::~MainWindow()
{
    delete ui;
}
