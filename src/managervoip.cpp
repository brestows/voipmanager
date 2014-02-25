#include "managervoip.h"
#include "ui_managervoip.h"
#include <amc.h>
#include "SQLite.h"
#include "settings.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QWidgetAction>
#include <QLabel>

ManagerVoIP::ManagerVoIP(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::ManagerVoIP)
{
    ui->setupUi(this);
    options = new Settings();
    correctHeight=0;
    correctHeight = ui->mainToolBar->size().height()
                  + ui->menuBar->size().height();
    createConnection();
    visibleToolBar(true);
    qDebug()<< "ToolBar: " << ui->mainToolBar->size().height();
    qDebug()<< "Correct: " << correctHeight;
    qDebug()<< "MenuBar: " << ui->menuBar->size().height();
    ui->mainToolBar->setWindowTitle(tr("Test"));
    ui->groupBox_2->setGeometry(100,100,150,250);
    QWidgetAction *wd = new QWidgetAction(this);
    QComboBox *bx = new QComboBox(this);
    bx->addItem("TEst");
    bx->addItem("tetet222");
    wd->setDefaultWidget(bx);

    QWidget *separator = new QWidget(this);
    separator->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);
    ui->mainToolBar->addWidget(separator);
    ui->mainToolBar->addWidget(new QLabel("Server: ", ui->mainToolBar));
    //ui->mainToolBar->addWidget(bx);
    ui->mainToolBar->addAction(wd);

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
    connect(ui->mnuView_ShowMenu,SIGNAL(triggered(bool)),SLOT(visibleMenuBar(bool)));
    connect(ui->mnuView_ShowToolBar,SIGNAL(triggered(bool)),SLOT(visibleToolBar(bool)));
    connect(ui->mnuView_ShowStatusBar,SIGNAL(triggered(bool)),ui->statusBar, SLOT(setVisible(bool)));
}

void ManagerVoIP::showSettings()
{
    options->exec();
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

void ManagerVoIP::visibleToolBar(bool vis)
{
    qDebug() << "------------";
    ui->mainToolBar->setVisible(vis);
    if(vis)
    {
        ui->mainToolBar->setWindowTitle(tr("Hide ToolBar"));
        correctHeight+=ui->mainToolBar->size().height();
        setCorrect();
    }
    else
    {
        ui->mainToolBar->setWindowTitle(tr("Show ToolBar"));
        correctHeight-=ui->mainToolBar->size().height();
        setCorrect();
    }
}

void ManagerVoIP::visibleMenuBar(bool vis)
{
    ui->menuBar->setVisible(vis);
    if(vis)
    {
        correctHeight+=ui->menuBar->size().height();
        setCorrect();
    }
    else
    {
        correctHeight-=ui->menuBar->size().height();
        setCorrect();
    }
}


void ManagerVoIP::setCorrect()
{
    QList<MovedBox *> allWid = this->findChildren<MovedBox *>();
    for(int i =0; i<allWid.size();++i)
        allWid.at(i)->setOffset(correctHeight);
}
