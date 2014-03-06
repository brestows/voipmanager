#include "asterisk.h"
#include <amc.h>
#include <QString>
#include <QDebug>
#include <amc/am_types.H>

Asterisk::Asterisk(QString host, QString port, QString username, QString pass)
{
    this->host = host.toStdString();
    this->port = (unsigned short)port.toUInt();
    this->username = username.toStdString();
    this->pass = pass.toStdString();

}
Asterisk::Asterisk(QObject *parent):QObject(parent)
{
    port=(unsigned short)5038;
}

Asterisk::Asterisk(QString host, QString port)
{
    this->host = host.toStdString();
    this->port = (unsigned short )port.toUInt();;
}

QList<QStringList> Asterisk::getPeers()
{
    vector<peer> peers = connectToHost();
    //int peers_count = peers.size();
    QList<QStringList> lstPeers;
    QStringList lst;
    if (peers.size()>0)
        foreach (peer test, peers)
        {


            lst<< QString::fromStdString(test.channel_type) <<
                  QString::fromStdString(test.object_name) <<
                  QString::fromStdString(test.description) <<
                  QString::fromStdString(test.ip_addr) <<
                  QString::fromStdString(test.status);
            lstPeers.push_back(lst);
            lst.clear();
        }
    return lstPeers;
}

vector<peer> Asterisk::connectToHost()
{
    vector<peer> peers;
    if(host.empty())
        qDebug() << "Host is not installed";
    else if(username.empty())
        qDebug() << "UserName is not installed";
    else if(pass.empty())
        qDebug() << "Password is empty!";
    else
    {
        amc ami;
        if(ami.connect(host, port))
            if(ami.login(host, port, username,pass))
                ami.SIP_peers(host, port,peers);
        ami.logoff(host,port);
        ami.disconnect(host,port);
    }
    return peers;
}

void Asterisk::setUserName(QString name)
{
    this->username = name.toStdString();
}

void Asterisk::setPassword(QString pass)
{
    this->pass = pass.toStdString();
}

void Asterisk::setHost(QString host)
{
    this->host = host.toStdString();
}

void Asterisk::setPort(QString port)
{
    this->port = (unsigned short)(port.toInt());
}
