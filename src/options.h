#ifndef OPTIONS_H
#define OPTIONS_H
#include <QMap>
class Options;
class QSettings;
class QString;

class DestroyOptions
{
private:
    Options *instance;
public:
    ~DestroyOptions();
    void initialize(Options *p);
};

class Options
{
private:
    static Options *instance;
    static DestroyOptions destroy;
//protected:
    Options();
    Options( const Options&);
    ~Options();
    friend class DestroyOptions;

    QSettings *settings;
public:
    static Options& getInstance();
    void saveOptions();
    void applyOptions();
    void writeOptions(QString, QString);
    void voip_saveSrv(QMap<QString, QString> srvSettings, QString srvName);
    QString voip_getPassword(QString nameSrv);
    QString voip_getUserName(QString nameSrv);
    QString voip_getPort(QString nameSrv);
    QString voip_getIP(QString nameSrv);
    QString readOptions(QString opt);
};

#endif // OPTIONS_H

