#include "options.h"
#include <QSettings>
#include <QString>
#include <QMap>

#include <QDebug>


Options * Options::instance = 0;
DestroyOptions Options::destroy;

DestroyOptions::~DestroyOptions() {
    delete instance;
}
void DestroyOptions::initialize(Options *p)
{
    instance = p;
}
Options& Options::getInstance()
{
    if(!instance)
    {
        instance = new Options();
        destroy.initialize(instance);
    }
    return *instance;
}

Options::Options()
{
    settings = new QSettings(QString("voipmanager"),QString("voipmanager"));
    qDebug()<<"File config: " << settings->fileName();
}

Options::~Options()
{
    delete settings;
}

QString Options::voip_getIP(QString nameSrv)
{
    QString ip = settings->value(QString("%1/host").arg(nameSrv), "192.168.0.1").toString();
    return ip;
}

QString Options::voip_getPort(QString nameSrv)
{
    QString port = settings->value(QString("%1/port").arg(nameSrv), "5038").toString();
    return port;
}

QString Options::voip_getUserName(QString nameSrv)
{
    QString name = settings->value(QString("%1/user").arg(nameSrv), "admin").toString();
    return name;
}

QString Options::voip_getPassword(QString nameSrv)
{
    QString pass = settings->value(QString("%1/pass").arg(nameSrv), "amp111").toString();
    return pass;
}

void Options::writeOptions(QString opt, QString value)
{
    settings->setValue(opt, value);
}

QString Options::readOptions(QString opt)
{
    QString str = settings->value(opt, QString("")).toString();
    return  str;
}

void Options::deleteSettingsGroup(QString grp)
{
    settings->beginGroup(grp);
    settings->remove("");
    settings->endGroup();
}
