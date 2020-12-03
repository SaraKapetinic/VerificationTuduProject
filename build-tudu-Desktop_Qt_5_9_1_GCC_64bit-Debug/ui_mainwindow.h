/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabMonth;
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *calendarMonths;
    QWidget *tabWeekTest;
    QTableWidget *tableWidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayoutTUDU;
    QMenuBar *menuBar;
    QMenu *menuMonths;
    QMenu *menuWeeks;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1277, 759);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 961, 611));
        tabMonth = new QWidget();
        tabMonth->setObjectName(QStringLiteral("tabMonth"));
        horizontalLayout = new QHBoxLayout(tabMonth);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        calendarMonths = new QCalendarWidget(tabMonth);
        calendarMonths->setObjectName(QStringLiteral("calendarMonths"));
        calendarMonths->setGridVisible(true);

        horizontalLayout->addWidget(calendarMonths);

        tabWidget->addTab(tabMonth, QString());
        tabWeekTest = new QWidget();
        tabWeekTest->setObjectName(QStringLiteral("tabWeekTest"));
        tableWidget = new QTableWidget(tabWeekTest);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        if (tableWidget->rowCount() < 96)
            tableWidget->setRowCount(96);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(15, 11, 931, 561));
        tableWidget->setMouseTracking(false);
        tableWidget->setAutoFillBackground(true);
        tableWidget->setRowCount(96);
        tableWidget->setColumnCount(7);
        tableWidget->horizontalHeader()->setMinimumSectionSize(52);
        tableWidget->verticalHeader()->setDefaultSectionSize(32);
        tabWidget->addTab(tabWeekTest, QString());
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(980, 0, 241, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        pushButton = new QPushButton(horizontalLayoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(980, 40, 241, 531));
        verticalLayoutTUDU = new QVBoxLayout(verticalLayoutWidget);
        verticalLayoutTUDU->setSpacing(6);
        verticalLayoutTUDU->setContentsMargins(11, 11, 11, 11);
        verticalLayoutTUDU->setObjectName(QStringLiteral("verticalLayoutTUDU"));
        verticalLayoutTUDU->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1277, 23));
        menuMonths = new QMenu(menuBar);
        menuMonths->setObjectName(QStringLiteral("menuMonths"));
        menuWeeks = new QMenu(menuBar);
        menuWeeks->setObjectName(QStringLiteral("menuWeeks"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMonths->menuAction());
        menuBar->addAction(menuWeeks->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(on_addTaskButtonClicked()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabMonth), QApplication::translate("MainWindow", "Month", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabWeekTest), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "TUDU List", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Add Task", Q_NULLPTR));
        menuMonths->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuWeeks->setTitle(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
