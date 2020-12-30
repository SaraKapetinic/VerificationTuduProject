#include "headers/init.h"

Init::Init(){}

void Init::setDays(Ui::MainWindow* ui, QDate currentDate){


    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek(ui);

    // Highlight current day header
    QColor headerColor = (255);
    ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setBackground(headerColor);

    int numOfDays = NUM_OF_WEEKDAYS - currentDayOfWeek;

    QVector<int> daysAdded(NUM_OF_WEEKDAYS);
    for (int i=NUM_OF_WEEKDAYS-1; i>=0; i--) {
        daysAdded[i] = numOfDays;
        numOfDays--;
    }

    // Fill list currentWeek and make header text

    for(int i = 0;i<NUM_OF_WEEKDAYS;i++){
            m_currentWeek.append(currentDate.addDays(daysAdded[i]));
            m_horizontalHeaders.append(ui->tableWidget->horizontalHeaderItem(i)->text().append(currentDate.addDays(daysAdded[i]).toString("\ndd.MM.yyyy.")));
    }

}

void Init::setHeaders(Ui::MainWindow* ui){

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek(ui);

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
    ui->tableWidget->verticalHeaderItem(getCurrentTimeRow(ui))->setBackground(QBrush(QColor("red")));
    ui->tableWidget->setCurrentCell(getCurrentTimeRow(ui), currentDayOfWeek-1);

}


QList<QDate> Init::getCurrentWeek() {
    return m_currentWeek;
}

int Init::getCurrentTimeRow(Ui::MainWindow* ui) {

    // Get current hour
    int currentHour = QTime::currentTime().hour();
    // Get current minutes -> in range [0,59]
    int currentMinutes = QTime::currentTime().minute();

    int minuteQuadrants = currentMinutes / 15;


    return 4*currentHour + minuteQuadrants;
}

int Init::getCurrentDayOfWeek(Ui::MainWindow* ui) {
    QDate currentDate = ui->calendarMonths->selectedDate();

    return currentDate.dayOfWeek();
}
