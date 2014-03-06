#include "managervoip.h"
#include "ui_managervoip.h"

#include "SQLite.h"
#include "settings.h"
#include "asterisk.h"
#include "options.h"
#include "peerstable.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QWidgetAction>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

ManagerVoIP::ManagerVoIP(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::ManagerVoIP)
{
    ui->setupUi(this);
    setting = new Settings();
    ui->mainToolBar->setWindowTitle(tr("Tool Bar"));
    createConnection();
    QWidgetAction *wd = new QWidgetAction(this);
    QComboBox *bx = new QComboBox();
    bx->addItem("TEst");
    bx->addItem("tetet222");
    connect(bx,SIGNAL(currentIndexChanged(QString)),SIGNAL(changeServer(QString)));
    wd->setDefaultWidget(bx);

    QWidget *separator = new QWidget(this);
    separator->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);
    ui->mainToolBar->addWidget(separator);
    ui->mainToolBar->addWidget(new QLabel("Server: ", ui->mainToolBar));
    ui->mainToolBar->addAction(wd);
    PeersTable *tabl = new PeersTable(this);
    connect(this,SIGNAL(changeServer(QString)), tabl, SLOT(changeServer(QString)));
    tabl->show();
}

ManagerVoIP::~ManagerVoIP()
{

    delete ui;
}

void ManagerVoIP::createConnection()
{
    connect(ui->mnuFile_Settings, SIGNAL(triggered()), SLOT(showSettings()));
    connect(ui->mnuFile_Exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->mnuHelp_AboutQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->mnuView_ShowMenu,SIGNAL(triggered(bool)),ui->menuBar, SLOT(setVisible(bool)));
    connect(ui->mnuView_ShowToolBar,SIGNAL(triggered(bool)),ui->mainToolBar,SLOT(setVisible(bool)));
    connect(ui->mnuView_ShowStatusBar,SIGNAL(triggered(bool)),ui->statusBar, SLOT(setVisible(bool)));
}

void ManagerVoIP::showSettings()
{
    setting->exec();
}

void ManagerVoIP::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
