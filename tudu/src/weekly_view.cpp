<<<<<<< HEAD:tudu/src/weeklyview.cpp
#include "headers/weeklyview.h"
=======
#include "headers/weekly_view.h"
>>>>>>> d61983e4fa8c3bc04d65e33b1cffeb5953927341:tudu/src/weekly_view.cpp

WeeklyView::WeeklyView(QDate date)
    :m_selectedDate(date)
{}

WeeklyView::WeeklyView()
    :m_selectedDate(QDate::currentDate())
{}
<<<<<<< HEAD:tudu/src/weeklyview.cpp


void WeeklyView::setDays(Ui::MainWindow* ui){
=======
>>>>>>> d61983e4fa8c3bc04d65e33b1cffeb5953927341:tudu/src/weekly_view.cpp

void WeeklyView::setDays(Ui::MainWindow* ui) {

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek();

    // Highlight current day header
    QColor headerColor = QColor(22, 12, 40);
    QColor textColor = QColor(225, 239, 230);
    ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setBackground(headerColor);
    ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setForeground(textColor);

    // Number of days till the end of the week
    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;

    // An array that helps us construct a weekly view for the selected date
    // (daysAdded[0] represents a distance from Monday, ..., daysAdded[6] distance from Sunday)
    QVector<int> daysAdded(NUM_OF_WEEKDAYS);
    for (int i=NUM_OF_WEEKDAYS-1; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }

    // Fill list currentWeek and make header text
    // The m_currentWeek represents list of dates that will be shown in the weekly view
    for(int i=0; i<NUM_OF_WEEKDAYS; i++) {
        m_currentWeek.append(m_selectedDate.addDays(daysAdded[i]));

        m_horizontalHeaders.append(ui->tableWidget->horizontalHeaderItem(i)->text().append(m_selectedDate.addDays(daysAdded[i]).toString("\ndd.MM.yyyy.")));

    }

}

<<<<<<< HEAD:tudu/src/weeklyview.cpp
void WeeklyView::setHeaders(Ui::MainWindow* ui){
=======
void WeeklyView::setHeaders(Ui::MainWindow* ui) {
>>>>>>> d61983e4fa8c3bc04d65e33b1cffeb5953927341:tudu/src/weekly_view.cpp

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek();

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels(m_horizontalHeaders);

    // Set row headers
    QString time;
    for (int i=0; i<HOURS_IN_DAY; i++) {
        for (int j=0; j<MINUTES_IN_HOUR; j+=MINUTE_INCREMENTS) {
            time = "";
            time.sprintf("%02d:%02d", i, j);
            m_verticalHeaders << time;
        }
    }

    ui->tableWidget->setVerticalHeaderLabels(m_verticalHeaders);
<<<<<<< HEAD:tudu/src/weeklyview.cpp
    ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setBackground(QBrush(QColor(22, 12, 40)));
    ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setForeground(QBrush(QColor(225, 239, 230)));
=======

    ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setBackground(QBrush(QColor("red")));

>>>>>>> d61983e4fa8c3bc04d65e33b1cffeb5953927341:tudu/src/weekly_view.cpp
    ui->tableWidget->setCurrentCell(getCurrentTimeRow(), currentDayOfWeek-1);

}

void WeeklyView::setDesign(Ui::MainWindow *ui) {
    ui->tableWidget->setStyleSheet("background-color: red;");
}

QList<QDate> WeeklyView::getCurrentWeek() {
    return m_currentWeek;
}

int WeeklyView::getCurrentTimeRow() {

    // Get current hour
    int currentHour = QTime::currentTime().hour();
    // Get current minutes -> in range [0,59]
    int currentMinutes = QTime::currentTime().minute();

    int minuteQuadrants = currentMinutes / 15;


    return 4*currentHour + minuteQuadrants;
}

int WeeklyView::getCurrentDayOfWeek() {
    return m_selectedDate.dayOfWeek();
<<<<<<< HEAD:tudu/src/weeklyview.cpp
}

void WeeklyView::execute(Ui::MainWindow* ui) {
    // Methods to set up mainwindow
    setDays(ui);
    setHeaders(ui);

    // Make table fill entire widget
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
=======
>>>>>>> d61983e4fa8c3bc04d65e33b1cffeb5953927341:tudu/src/weekly_view.cpp
}
