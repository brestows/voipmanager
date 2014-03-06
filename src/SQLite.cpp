#include "SQLite.h"
 
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql>

#include "options.h"
cDataBase::cDataBase()
{
    //строка соединения
    QString connection = QString(QSqlDatabase::defaultConnection);
    //это нужно, чтобы не возникало ошибки о повторном соединении, так надо
    if (QSqlDatabase::contains(connection)) {
        m_db = QSqlDatabase::database(connection);
    } else {
        //подключаемся через QSQLITE драйвер
        m_db = QSqlDatabase::addDatabase(Options::getInstance().readOptions(QString("CDR_DateBase/type")), connection);
        //вписываем имя БД
        m_db.setHostName(Options::getInstance().readOptions(QString("CDR_DateBase/host")));
        m_db.setDatabaseName(Options::getInstance().readOptions(QString("CDR_DateBase/db")));
        m_db.setUserName(Options::getInstance().readOptions(QString("CDR_DateBase/user")));
        m_db.setPassword(Options::getInstance().readOptions(QString("CDR_DateBase/pass")));
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
    query.addBindValue(id);
    query.addBindValue(name);
 
    if (!query.exec()) {
        QMessageBox::warning(0,"Error", query.lastError().text());
        return -1;
    }
    int rer = query.lastInsertId().toInt();
    return rer;
 
}
