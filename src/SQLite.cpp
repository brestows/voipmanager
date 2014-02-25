#include "SQLite.h"
 
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql>
 
cDataBase::cDataBase()
{
    //строка соединения
    QString connection = QString(QSqlDatabase::defaultConnection);
    //это нужно, чтобы не возникало ошибки о повторном соединении, так надо
    if (QSqlDatabase::contains(connection)) {
        m_db = QSqlDatabase::database(connection);
    } else {
        //подключаемся через QSQLITE драйвер
        m_db = QSqlDatabase::addDatabase("QMYSQL", connection);
        //вписываем имя БД
        m_db.setHostName("192.168.0.11");
        m_db.setDatabaseName("asteriskcdrdb");
        m_db.setUserName("voip");
        m_db.setPassword("ZGE1YTY4Yz");
        open_db = m_db.open();
        if(open_db)
        {
            qDebug() << "DataBase is Open!";
        }
        else
        {
            qDebug()<< m_db.lastError().text();

        }
    }
}
 
QSqlDatabase cDataBase::get_db()
{
    return m_db;
}
 
bool cDataBase::isOpen()
{
    return open_db;
}
 
int cDataBase::Insert(int id, QString name)
{
    QSqlQuery query;
 
    query.prepare("INSERT INTO names2 (id, name) VALUES (?, ?)");
    //addBindValue решает проблему экранирования, поэтому добавлять значения надо именно этой функцией
    query.addBindValue(id);
    query.addBindValue(name);
 
    if (!query.exec()) {
        QMessageBox::warning(0,"Error", query.lastError().text());
        return -1;
    }
    //получаем id вставленной записи
    int rer = query.lastInsertId().toInt();
   
    return rer;
 
}
