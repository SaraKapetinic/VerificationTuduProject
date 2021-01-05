#include "headers/weeklyview.h"

WeeklyView::WeeklyView(QDate date)
    :m_selectedDate(date)
{}

WeeklyView::WeeklyView()
    :m_selectedDate(QDate::currentDate())
{}

void WeeklyView::setDays(Ui::MainWindow* ui) {

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek();

    // Highlight current day header
    QColor headerColor = QColor(22, 12, 40);
    QColor textColor = QColor(225, 239, 230);
    for (int i=0; i<7; i++) {
            ui->tableWidget->horizontalHeaderItem(i)->setBackground(textColor);
            ui->tableWidget->horizontalHeaderItem(i)->setForeground(headerColor);
        }
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
    for(int i = 0;i<NUM_OF_WEEKDAYS;i++){
                m_currentWeek.append(m_selectedDate.addDays(daysAdded[i]));
                m_horizontalHeaders
                    .append(m_selectedDate.addDays(daysAdded[i]).toString("dddd\ndd.MM.yyyy."));
        }

}

void WeeklyView::setHeaders(Ui::MainWindow* ui) {

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
    ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setBackground(QBrush(QColor(22, 12, 40)));
    ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setForeground(QBrush(QColor(225, 239, 230)));
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
}

void WeeklyView::execute(Ui::MainWindow* ui) {
    // Methods to set up mainwindow
    setDays(ui);
    setHeaders(ui);

    // Make table fill entire widget
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
