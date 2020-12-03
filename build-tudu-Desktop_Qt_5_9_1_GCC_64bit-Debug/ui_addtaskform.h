/********************************************************************************
** Form generated from reading UI file 'addtaskform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTASKFORM_H
#define UI_ADDTASKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTaskForm
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QTimeEdit *timeEdit;
    QLabel *label;
    QDateEdit *dateEdit_2;
    QTimeEdit *timeEdit_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QComboBox *comboBox;

    void setupUi(QDialog *AddTaskForm)
    {
        if (AddTaskForm->objectName().isEmpty())
            AddTaskForm->setObjectName(QStringLiteral("AddTaskForm"));
        AddTaskForm->resize(501, 500);
        gridLayout = new QGridLayout(AddTaskForm);
        gridLayout->setSpacing(5);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(10, 10, 10, 10);
        scrollArea = new QScrollArea(AddTaskForm);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 481, 480));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        dateEdit = new QDateEdit(frame_2);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setCalendarPopup(true);

        horizontalLayout_2->addWidget(dateEdit);

        timeEdit = new QTimeEdit(frame_2);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setTimeSpec(Qt::LocalTime);

        horizontalLayout_2->addWidget(timeEdit);

        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        dateEdit_2 = new QDateEdit(frame_2);
        dateEdit_2->setObjectName(QStringLiteral("dateEdit_2"));
        dateEdit_2->setCalendarPopup(true);

        horizontalLayout_2->addWidget(dateEdit_2);

        timeEdit_2 = new QTimeEdit(frame_2);
        timeEdit_2->setObjectName(QStringLiteral("timeEdit_2"));

        horizontalLayout_2->addWidget(timeEdit_2);


        gridLayout_2->addWidget(frame_2, 1, 0, 1, 1);

        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QFont font;
        font.setPointSize(12);
        pushButton->setFont(font);

        gridLayout_2->addWidget(pushButton, 7, 0, 1, 1);

        lineEdit = new QLineEdit(scrollAreaWidgetContents);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        font1.setWeight(75);
        lineEdit->setFont(font1);
        lineEdit->setMaxLength(1024);
        lineEdit->setFrame(false);

        gridLayout_2->addWidget(lineEdit, 0, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout_2->addWidget(plainTextEdit, 6, 0, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout->addWidget(checkBox);

        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        gridLayout_2->addWidget(frame, 5, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(AddTaskForm);

        QMetaObject::connectSlotsByName(AddTaskForm);
    } // setupUi

    void retranslateUi(QDialog *AddTaskForm)
    {
        AddTaskForm->setWindowTitle(QApplication::translate("AddTaskForm", "Add New Task", Q_NULLPTR));
        label_3->setText(QApplication::translate("AddTaskForm", "From", Q_NULLPTR));
        dateEdit->setDisplayFormat(QApplication::translate("AddTaskForm", "dd.MM.yyyy.", Q_NULLPTR));
        label->setText(QApplication::translate("AddTaskForm", "to", Q_NULLPTR));
        dateEdit_2->setDisplayFormat(QApplication::translate("AddTaskForm", "dd.MM.yyyy.", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AddTaskForm", "Save", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("AddTaskForm", "Add title", Q_NULLPTR));
        plainTextEdit->setPlaceholderText(QApplication::translate("AddTaskForm", "Add description", Q_NULLPTR));
        checkBox->setText(QApplication::translate("AddTaskForm", "All day", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("AddTaskForm", "Does not repeat", Q_NULLPTR)
         << QApplication::translate("AddTaskForm", "Daily", Q_NULLPTR)
         << QApplication::translate("AddTaskForm", "Weekly", Q_NULLPTR)
         << QApplication::translate("AddTaskForm", "Monthly", Q_NULLPTR)
         << QApplication::translate("AddTaskForm", "Annually", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class AddTaskForm: public Ui_AddTaskForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTASKFORM_H
