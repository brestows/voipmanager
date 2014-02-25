#include "settings.h"
#include "ui_settings.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QRegExpValidator>
#include <QList>
#include <QSettings>

#include <QDebug>


Settings::Settings(QWidget *parent) :    QDialog(parent),    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->AreaSettings->setCurrentIndex(0);
    ui->lstSection->setCurrentRow(0);
    settingsForm();
    options = new QSettings("managervoip.conf", QSettings::NativeFormat);
    options->setParent(this);
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
}

void Settings::changeSection(QListWidgetItem *current,QListWidgetItem *previous)
{
    if(!current)
    {
        current=previous;
    }
    ui->AreaSettings->setCurrentIndex(ui->lstSection->row(current));
}

void Settings::saveSettings()
{
    options->setValue("CDR/driver", "MYSQL");
    options->sync();
}
