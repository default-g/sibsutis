#include "databaseconnection.h"
#include <QDebug>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>


DatabaseConnection::DatabaseConnection(const QString &path)
{
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName(path);
    if (!this->database.open()) {
        qDebug() << "ERROR";
    } else {
        qDebug() << "WORKING!";
    }
}


void DatabaseConnection::addRecord(const QString name, const float time) {
    QSqlQuery query;
    query.prepare("INSERT INTO leaderboard (name, time) VALUES (:name, :time)");
    query.bindValue(":name", name);
    query.bindValue(":time", time);
    if (query.exec()) {
        qDebug() << "WORKING!";
    } else {
        qDebug() << "NOT WORKING(";
    }
}


QList<QList<QString> > DatabaseConnection::getRecords() {
    QSqlQuery query(this->database);
    QList<QList<QString> > records;
    if (query.exec("SELECT name, time FROM leaderboard ORDER BY time")) {
        while(query.next()) {
            QList<QString> tmp;
            QString name = query.value(0).toString();
            QString time = QTime::fromMSecsSinceStartOfDay(query.value(1).toInt()).toString("HH:mm:ss");
            tmp.append(name);
            tmp.append(time);
            records.append(tmp);
        }
    } else {
        qDebug() << "FAIL";
        qDebug() << query.lastError();
    }

    return records;

}
