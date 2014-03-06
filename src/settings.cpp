#include "settings.h"
#include "ui_settings.h"
#include "options.h"
#include "qglobal.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QRegExpValidator>
#include <QList>
#include <QSettings>
#include <QMessageBox>

#include <QDebug>

//#define qDebug() qDebug() << __LINE__ <<  " " << Q_FUNC_INFO

Settings::Settings(QWidget *parent) :    QDialog(parent),    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->AreaSettings->setCurrentIndex(0);
    ui->lstSection->setCurrentRow(0);
    settingsForm();
    connect(ui->cmdSave, SIGNAL(clicked()), this, SLOT(saveSettings()));
}

void Settings::saveSettingsCDR()
{
    QString value = "";
    if(ui->cmbCDR_DataBase->currentText()=="MariaDB")
        value = "QMYSQL";
    else if (ui->cmbCDR_DataBase->currentText()=="PostgreSQL")
        value = "QPSQL";
    Options::getInstance().writeOptions(QString("CDR_DateBase/db"), ui->txtCDR_dbName->text());
    Options::getInstance().writeOptions(QString("CDR_DateBase/host"), ui->txtCDR_Host->Text());
    Options::getInstance().writeOptions(QString("CDR_DateBase/pass"), ui->txtCDR_Password->text());
    Options::getInstance().writeOptions(QString("CDR_DateBase/type"), value);
    Options::getInstance().writeOptions(QString("CDR_DateBase/user"), ui->txtCDR_UserName->text());
    if(!ui->txtCDR_SQLQuery->toPlainText().isEmpty())
        Options::getInstance().writeOptions(QString("CDR_DateBase/query"), ui->txtCDR_SQLQuery->toPlainText());
    Options::getInstance().writeOptions(QString("CDR_DateBase/enable"), QString("%1").arg((int)ui->grpRecord->isChecked()));
}

void Settings::saveSettingsVoIPServer()
{
    QMapIterator<QString, QMap<QString, QString> > i(lstVoipServer);
    QString lstSrv="";
    QMap<QString, QString>::const_iterator j;
    while (i.hasNext())
    {
        i.next();
        lstSrv.append(QString("%1,").arg(i.key()));
        j= i.value().constBegin();
        while (j !=i.value().constEnd())
        {
            Options::getInstance().writeOptions(QString("%1/%2").arg(i.key()).arg(j.key()), j.value());
            j++;
        }
    }
    Options::getInstance().writeOptions(QString("ServerList/server"), lstSrv.left(lstSrv.size()-1));
    for(int p=0;p<removeServer.size();p++)
    {
        Options::getInstance().deleteSettingsGroup(removeServer.at(p));
    }
}

void Settings::saveSettings()
{
    saveSettingsCDR();
    saveSettingsVoIPServer();

    this->close();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Settings::readSettingsCDR()
{
    if(ui->grpRecord->isChecked())
    {
        ui->txtCDR_dbName->setText( Options::getInstance().readOptions(QString("CDR_DateBase/db")));
        ui->txtCDR_Host->setText(Options::getInstance().readOptions(QString("CDR_DateBase/host")));
        ui->txtCDR_Password->setText(Options::getInstance().readOptions(QString("CDR_DateBase/pass")));
        QString value = Options::getInstance().readOptions(QString("CDR_DateBase/type"));
        if (value == "QMYSQL")
            ui->cmbCDR_DataBase->setCurrentText("MariaDB");
        else if (value == "QPSQL")
            ui->cmbCDR_DataBase->setCurrentText("PostgreSQL");
        ui->txtCDR_UserName->setText(Options::getInstance().readOptions(QString("CDR_DateBase/user")));
        ui->txtCDR_TableName->setText(Options::getInstance().readOptions(QString("CDR_DateBase/table")));
        ui->txtCDR_SQLQuery->setText(Options::getInstance().readOptions(QString("CDR_DateBase/query")));
        ui->grpRecord->setChecked((Options::getInstance().readOptions(QString("CDR_DateBase/enable"))).toInt());
    }
}

void Settings::readSettingsVoipServer()
{
    QStringList lst = Options::getInstance().readOptions(QString("ServerList/server")).split(",");
    ui->lstVoip_Server->addItems(lst);
    QMap <QString, QString> tmp;
    lstVoipServer.clear();
    for(int i=0;i<lst.size();i++)
    {
         tmp.insert(QString("host"), Options::getInstance().readOptions(QString("%1/host").arg(lst.at(i))));
         tmp.insert(QString("pass"), Options::getInstance().readOptions(QString("%1/pass").arg(lst.at(i))));
         tmp.insert(QString("user"),Options::getInstance().readOptions(QString("%1/user").arg(lst.at(i))));
         tmp.insert(QString("port"),Options::getInstance().readOptions(QString("%1/port").arg(lst.at(i))));
         lstVoipServer.insert(lst.at(i), tmp);
    }
}

void Settings::settingsForm()
{
    QListWidgetItem *item=0;
    QStringList lst;
    lst << tr("General") << tr("VoIP") << tr("Call Detail Record");

    foreach (QString str, lst)
    {
        item = new QListWidgetItem(ui->lstSection);
        item->setText(str);
        item->setIcon(QIcon(":/cdr.png"));
    }
    connect(ui->lstSection, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),SLOT(changeSection(QListWidgetItem*,QListWidgetItem*)));
    connect(ui->cmdClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->cmdVoip_DelServer, SIGNAL(clicked()),SLOT(voip_delSrv()));
    connect(ui->cmdVoip_AddServer, SIGNAL(clicked()),SLOT(voip_addSrv()));
    connect(ui->lstVoip_Server, SIGNAL(currentTextChanged(QString)),SLOT(voip_changeSrv(QString)));
    readSettingsCDR();
    readSettingsVoipServer();
}

void Settings::changeSection(QListWidgetItem *current,QListWidgetItem *previous)
{
    if(!current)
    {
        current=previous;
    }
    ui->AreaSettings->setCurrentIndex(ui->lstSection->row(current));
}

void Settings::voip_addSrv()
{
    if(ui->txtVoip_SrvName->text().isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Server name is empty!"), QMessageBox::Ok);
        return;
    }
    else if(ui->txtVoip_Host->Text().isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Host server is empty!"), QMessageBox::Ok);
        return;
    }
    else if(ui->txtVoip_Port->text().isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Port server is empty!"), QMessageBox::Ok);
        return;
    }
    else if(ui->txtVoip_UserName->text().isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("UserName is empty!"), QMessageBox::Ok);
        return;
    }
    else if(ui->txtVoip_Pass->text().isEmpty())
    {
        if(QMessageBox::information(this, tr("Error"), tr("Password server is empty!Used empty password?"), QMessageBox::Yes, QMessageBox::No)==QMessageBox::No)
            return;
    }
    if(lstVoipServer.contains(ui->txtVoip_SrvName->text()))
    {
        QMessageBox::information(this, tr("Error"), tr("Server %1 is already listed.Enter other Name").arg(ui->txtVoip_SrvName->text()), QMessageBox::Ok);
        return;
    }
    QMap<QString, QString> tmp;
    tmp.insert(QString("host"), ui->txtVoip_Host->Text());
    tmp.insert(QString("port"), ui->txtVoip_Port->text());
    tmp.insert(QString("user"), ui->txtVoip_UserName->text());
    tmp.insert(QString("pass"), ui->txtVoip_Pass->text());
    lstVoipServer.insert(ui->txtVoip_SrvName->text(), tmp);
    ui->lstVoip_Server->addItem(ui->txtVoip_SrvName->text());
    qDebug() << "Count srv " << lstVoipServer.size();
}

void Settings::voip_delSrv()
{
    if (ui->lstVoip_Server->selectedItems().count()> 0)
    {
        QString srvName = ui->lstVoip_Server->currentItem()->text();
        delete ui->lstVoip_Server->takeItem(ui->lstVoip_Server->row(ui->lstVoip_Server->currentItem()));
        lstVoipServer.remove(srvName);
        ui->txtVoip_Host->clear();
        ui->txtVoip_Pass->clear();
        ui->txtVoip_Port->clear();
        ui->txtVoip_SrvName->clear();
        ui->txtVoip_UserName->clear();
        removeServer.push_back(srvName);
    }
    else
    {
         qDebug() << "DON'T SELECTED ITEM!";
    }
}

void Settings::voip_changeSrv(QString srv)
{
    if(!srv.isEmpty())
    {
        QMap<QString, QString> tmp = lstVoipServer[srv];
        ui->txtVoip_Host->setText(tmp["host"]);
        ui->txtVoip_Port->setText(tmp["port"]);
        ui->txtVoip_UserName->setText(tmp["user"]);
        ui->txtVoip_Pass->setText(tmp["pass"]);
        ui->txtVoip_SrvName->setText(srv);
        qDebug() << __LINE__ <<  " " << Q_FUNC_INFO <<  " " << srv;
    }
}
