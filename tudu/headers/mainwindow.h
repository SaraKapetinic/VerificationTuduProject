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

private slots:
  void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
