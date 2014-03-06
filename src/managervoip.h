#ifndef MANAGERVOIP_H
#define MANAGERVOIP_H

#include <QMainWindow>

class QSqlTableModel;
class cDataBase;
class Settings;
namespace Ui {
class ManagerVoIP;
}

class ManagerVoIP : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerVoIP(QWidget *parent = 0);
    ~ManagerVoIP();

protected:
    void changeEvent(QEvent *e);


private:
    Ui::ManagerVoIP *ui;
    QSqlTableModel *model;
    cDataBase *cdr_db;
    Settings *setting;
    void createConnection();

private slots:
    void showSettings();
signals:
    void changeServer(QString);
};

#endif // MANAGERVOIP_H
