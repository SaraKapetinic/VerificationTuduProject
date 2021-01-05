#include "headers/weeklyview.h"

WeeklyView::WeeklyView(Ui::MainWindow* ui, QDate date)
    :m_ui(ui), m_selectedDate(date)
{}

WeeklyView::WeeklyView(Ui::MainWindow* ui)
    :m_ui(ui), m_selectedDate(QDate::currentDate())
{}

void WeeklyView::setDays() {

    // Ordinal number of current day (Monday = 1; ... ; Sunday = 7)
    int currentDayOfWeek = getCurrentDayOfWeek();

    // Highlight current day header
    QColor headerColor = QColor(22, 12, 40);
    QColor textColor = QColor(225, 239, 230);
    for (int i=0; i<7; i++) {
            m_ui->tableWidget->horizontalHeaderItem(i)->setBackground(textColor);
            m_ui->tableWidget->horizontalHeaderItem(i)->setForeground(headerColor);
        }
    m_ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setBackground(headerColor);
    m_ui->tableWidget->horizontalHeaderItem(currentDayOfWeek-1)->setForeground(textColor);

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
            time.sprintf("%02d:%02d", i, j);
            m_verticalHeaders << time;
        }
    }

    m_ui->tableWidget->setVerticalHeaderLabels(m_verticalHeaders);
    m_ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setBackground(QBrush(QColor(22, 12, 40)));
    m_ui->tableWidget->verticalHeaderItem(getCurrentTimeRow())->setForeground(QBrush(QColor(225, 239, 230)));
    m_ui->tableWidget->setCurrentCell(getCurrentTimeRow(), currentDayOfWeek-1);

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
        auto model = m_ui->tableWidget->model();
        foreach(const QString& key, savedTasks.keys()){
            // TODO add a check to see if the task is in the current week
            // if (isCurrentWeem(key)) or something like that

            auto currentTask = new Task(savedTasks.value(key));
            auto taskColumn = currentTask->getStartTime().date().dayOfWeek() - 1;
            auto task_row = currentTask->getStartTime().time().msecsSinceStartOfDay() / (1000 * 60 * 15);
            auto task_row_span = currentTask->getEndTime().time().msecsSinceStartOfDay() / (1000 * 60 * 15);
            auto span = task_row_span - task_row;

            QStringList splitDate = m_ui->tableWidget->horizontalHeaderItem(taskColumn)->text().split("\n");

            QDate dateHeader = QDate::fromString(splitDate[1], "dd.MM.yyyy.");
            QDateTime dateTask = QDateTime::fromString(key, "dd.MM.yyyy.hh:mm:ms");

            std::cout << dateHeader.toString().toStdString() << std::endl;
            std::cout << dateTask.date().toString().toStdString() << std::endl;

            if(dateHeader == dateTask.date()){
                auto item = new QTableWidgetItem();
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setData(NAME_ROLE, QVariant::fromValue<QString>(currentTask->getName()));
                item->setData(ENDTIME_ROLE, QVariant::fromValue<QDateTime>(currentTask->getEndTime()));
                item->setData(DESCRIPTION_ROLE, QVariant::fromValue<QString>(currentTask->getDescription()));
                item->setData(CREATIONTIME_ROLE,QVariant::fromValue<QString>(currentTask->getCreationTimeString()));
                item->setText(currentTask->getName());
                m_ui->tableWidget->setItem(task_row, taskColumn, item);
                m_ui->tableWidget->setSpan(task_row, taskColumn, span, 1);
            }else{
                std::cout << "usao sam ovde" << std::endl;
                auto item = new QTableWidgetItem();
                item->setText("");
                m_ui->tableWidget->setItem(task_row, taskColumn, item);
            }

        }
    }else{
        std::cerr << "No tasks in file" << std::endl;
    }
}

void WeeklyView::execute() {
    // Methods to set up mainwindow
    setDays();
    setHeaders();
    loadFromJson();

    // Make table fill entire widget
    m_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
