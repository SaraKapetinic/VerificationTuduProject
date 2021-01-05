#ifndef ADDTASKFORMTUDU_H
#define ADDTASKFORMTUDU_H

#include <QDialog>
#include "headers/task.h"

#define HIGH_PRIORITY (0)
#define MID_PRIORITY (1)
#define LOW_PRIORITY (2)

namespace Ui {
class AddTaskFormTudu;
}

class AddTaskFormTudu : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskFormTudu(QWidget *parent = nullptr);
    ~AddTaskFormTudu();
    void setTitle(QString title);
    void setDescription(QString description);
    void setPriority(int priority);

private slots:
    void on_tuduTaskSave_clicked();

signals:
    void sendToTuduList(QString title, QString desc, int priority);

private:
    Ui::AddTaskFormTudu *ui;
};

#endif // ADDTASKFORMTUDU_H
