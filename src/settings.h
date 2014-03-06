#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QMap>

class QListWidgetItem;
class QSettings;


namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    void saveSettingsVoIPServer();
    void readSettingsVoipServer();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::Settings *ui;
    void settingsForm();
    void readSettingsCDR();
    void saveSettingsCDR();
    QMap <QString,QMap<QString, QString> > lstVoipServer;
    QStringList removeServer;
private slots:
    void changeSection(QListWidgetItem*,QListWidgetItem*);
    void saveSettings();
    void voip_addSrv();
    void voip_delSrv();
    void voip_changeSrv(QString);
};

#endif // SETTINGS_H
