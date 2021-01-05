#include "headers/weeklyview.h"

WeeklyView::WeeklyView(Ui::MainWindow* ui, QDate date)
    :m_ui(ui), m_selectedDate(date)
{}

WeeklyView::WeeklyView(Ui::MainWindow* ui)
    :m_ui(ui), m_selectedDate(QDate::currentDate())
{}

void WeeklyView::clearView() {
    // Reset header colors
    for (int i=0; i<7; i++) {
            m_ui->tableWidget->horizontalHeaderItem(i)->setBackground(m_headerPrimaryColor);
            m_ui->tableWidget->horizontalHeaderItem(i)->setForeground(m_headerSecondaryColor);
    }

    // Clear content of a weekly view
    for (int i=0; i<NUM_OF_WEEKDAYS; i++) {
        for (int j=0; j<HOURS_IN_DAY*(MINUTES_IN_HOUR/MINUTE_INCREMENTS); j++) {
            auto item = new QTableWidgetItem();
            item->setText("");
            m_ui->tableWidget->setSpan(j, i, 1, 1);
            m_ui->tableWidget->setItem(j, i, item);
        }
    }
}

void WeeklyView::setDays() {

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek();

    // Highlight current day header
    m_ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setBackground(m_headerSecondaryColor);
    m_ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setForeground(m_headerPrimaryColor);

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

void WeeklyView::setHeaders() {

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek();

    // Set column headers
    m_ui->tableWidget->setHorizontalHeaderLabels(m_horizontalHeaders);

    // Set row headers
    QString time;
    for (int i=0; i<HOURS_IN_DAY; i++) {
        for (int j=0; j<MINUTES_IN_HOUR; j+=MINUTE_INCREMENTS) {
            time = "";
//            time.sprintf("%02d:%02d", i, j);
            time = QString("%1:%2")
                    .arg(i, 2, 10, QLatin1Char('0'))
                    .arg(j, 2, 10, QLatin1Char('0'));
            m_verticalHeaders << time;
        }
    }

    m_ui->tableWidget->setVerticalHeaderLabels(m_verticalHeaders);
    m_ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setBackground(QBrush(QColor(22, 12, 40)));
    m_ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setForeground(QBrush(QColor(225, 239, 230)));
    m_ui->tableWidget->setCurrentCell(getCurrentTimeRow(), currentDayOfWeek-1);

}

QList<QDate> WeeklyView::getCurrentWeek() const {
    return m_currentWeek;
}

int WeeklyView::getCurrentTimeRow() const {

    // Get current hour
    int currentHour = QTime::currentTime().hour();
    // Get current minutes -> in range [0,59]
    int currentMinutes = QTime::currentTime().minute();

    int minuteQuadrants = currentMinutes / 15;


    return 4*currentHour + minuteQuadrants;
}

int WeeklyView::getCurrentDayOfWeek() const {
    return m_selectedDate.dayOfWeek();
}

void WeeklyView::loadFromJson(){
    // Load from file
    // TODO load the file location using a macro from task.cpp
    QString fileLocation = QString("%1/weekly_tasks.json")
            .arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    // Open file for reading
    QFile file(fileLocation);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read JSON
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    file.close();
    // Get array so we can see number of tasks in file
    auto savedTasks = jsonDocument.object();

    // Put tasks from file to Weekly table
    if(savedTasks.size() != 0){
        foreach(const QString& key, savedTasks.keys()){
            QDate dateTask = QDateTime::fromString(savedTasks.value(key)["startTime"]
                    .toString(), START_END_TIME_FORMAT)
                    .date();

            // Check if the task is in the current week
            if (dateTask >= m_currentWeek.first() && dateTask <= m_currentWeek.last()) {

                auto currentTask = new Task(savedTasks.value(key));
                auto taskColumn = currentTask->getTaskColumn();
                auto taskRow = currentTask->getTaskRow();
                auto span = currentTask->getTaskSpan();

                auto item = new QTableWidgetItem();
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setData(NAME_ROLE, QVariant::fromValue<QString>(currentTask->getName()));
                item->setData(ENDTIME_ROLE, QVariant::fromValue<QDateTime>(currentTask->getEndTime()));
                item->setData(DESCRIPTION_ROLE, QVariant::fromValue<QString>(currentTask->getDescription()));
                item->setData(CREATIONTIME_ROLE,QVariant::fromValue<QString>(currentTask->getCreationTimeString()));
                item->setText(currentTask->getName());
                QColor taskColor = QColor(239, 138, 23);
                item->setBackground(taskColor);
                item->setTextAlignment(Qt::AlignCenter);
                QFont font;
                font.setFamily("Ubuntu");
                font.setPointSize(12);
                item->setFont(font);
                m_ui->tableWidget->setItem(taskRow, taskColumn, item);
                m_ui->tableWidget->setSpan(taskRow, taskColumn, span+2, 1);
            }
        }
    }else{
        std::cerr << "No tasks in the file." << std::endl;
    }
}

void WeeklyView::execute() {
    // Methods to set up a mainwindow
    clearView();
    setDays();
    setHeaders();
    loadFromJson();

    // Make table fill entire widget
    m_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
