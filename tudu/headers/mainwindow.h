#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  void on_addTaskButtonClicked();
  void recieveFromTask(QString taskTitle, int row, int column, int span);
  void recieveInTuduList(QString title, QString desc, int priority);

private slots:
  void on_tableWidget_cellDoubleClicked(int row, int column);

  void on_calendarMonths_activated(const QDate &date);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
