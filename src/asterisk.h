#ifndef ASTERISK_H
#define ASTERISK_H

#include <QObject>
class QString;
class QStringList;
class amc;
struct peer;
class Asterisk : public QObject
{
    Q_OBJECT
private:
    std::string host,username, pass;
    short unsigned int port;
    std::vector<peer> connectToHost();
    bool disconnectFromHost();
public:
    explicit Asterisk(QObject *parent = 0);
    Asterisk(QString host, QString port, QString username, QString pass);
    Asterisk(QString host, QString port);
    void setUserName(QString);
    void setPassword(QString);
    void setHost(QString);
    void setPort(QString);
    void setConfig(QString);
    QList<QStringList> getPeers();
signals:

public slots:

};

#endif // ASTERISK_H
