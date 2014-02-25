#ifndef CDATABASE_H
#define CDATABASE_H
 
#include <string>
#include <QtSql/QSqlDatabase>
#include <QtGui>
 
class cDataBase
{
public:
    cDataBase();
 
public:
    int Insert(int id, QString  name);
    QSqlDatabase get_db();
    bool isOpen();

private:
    QSqlDatabase m_db; //наша БД
    bool open_db;
};
 
#endif // CDATABASE_H
