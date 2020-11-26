#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
