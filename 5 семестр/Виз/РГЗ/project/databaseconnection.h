#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

#define DEFAULT_DATABASE_PATH "/Users/defaultid/Google Drive/учоба/5 семестр/Виз/РГЗ/project/database.db"

class DatabaseConnection
{
public:
    DatabaseConnection(const QString &path);
    void addRecord(const QString name, const float time);
    QList<QList<QString> >  getRecords();
private:
    QSqlDatabase database;
};

#endif // DATABASECONNECTION_H
