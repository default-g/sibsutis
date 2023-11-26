#include "leaderboard.h"
#include "ui_leaderboard.h"
#include "databaseconnection.h"
#include <QList>
#include <QString>

LeaderBoard::LeaderBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);
    DatabaseConnection databaseConnection = DatabaseConnection(DEFAULT_DATABASE_PATH);
    auto records = databaseConnection.getRecords();
    for(int i = 0; i < records.size(); i++) {
        this->ui->tableWidget->insertRow(i);
        for(int j = 0; j < records[i].size(); j++) {
            qDebug() << records[i][j];
            this->ui->tableWidget->setItem(i, j, new QTableWidgetItem(records[i][j]));
        }
    }
}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}
