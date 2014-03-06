
#include "peerstable.h"
#include "movedbox.h"
#include "asterisk.h"
#include "options.h"

#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMenu>

#include <QDebug>

#define X 0
#define Y 1
#define W 0
#define H 1

PeersTable::PeersTable(QWidget *parent) :   MovedBox(parent)
{
    this->setObjectName("PeersTable");

    QString positions = Options::getInstance().readOptions(QString("%1/positions").arg(objectName()));
    QString size = Options::getInstance().readOptions(QString("%1/size").arg(objectName()));
    if(positions.isEmpty())
    {
        x = 20;
        y = 20;
    }
    else
    {
        x = positions.split(",").at(X).toInt();
        y = positions.split(",").at(Y).toInt();
    }
    if(size.isEmpty())
    {
        w = 150;
        h = 250;
    }
    else
    {
        w = size.split(",").at(W).toInt();
        h = size.split(",").at(H).toInt();
    }
    settingsGrid();
}

PeersTable::~PeersTable()
{
// Options::getInstance().writeOptions(QString("%1/caries").arg(objectName()), QString("-------"));
}

void PeersTable::settingsGrid()
{

    Asterisk aster;
    QHBoxLayout *vbox = new QHBoxLayout;
    aster.setHost(Options::getInstance().voip_getIP(QString("Test")));
    aster.setPort(Options::getInstance().voip_getPort(QString("Test")));
    aster.setUserName(Options::getInstance().voip_getUserName(QString("Test")));
    aster.setPassword(Options::getInstance().voip_getPassword(QString("Test")));
    QList<QStringList> lst = aster.getPeers();
    if(lst.size()>0)
    {
        if (!tablePeers)
            tablePeers = new QTableWidget(lst.size(), lst.at(0).size());
        else
            tablePeers->clear();
        tablePeers->setSelectionMode(QAbstractItemView::SingleSelection);
        tablePeers->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablePeers->verticalHeader()->setDefaultSectionSize(22);
        tablePeers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablePeers->horizontalHeader()->setStretchLastSection(true);
        vbox->addWidget(tablePeers);
        this->setLayout(vbox);
        this->setTitle(tr("Table Peers"));
        QStringList tmp;
        QColor background;
        background.setRgb(79,105,134);
        QTableWidgetItem *item;
        for(int i=0; i<lst.size();i++)
        {
            tmp = lst.at(i);
            for(int j=0; j< tmp.size();j++)
            {
                item = new QTableWidgetItem(tmp.at(j));
                if(tmp.at(0) == "SIP")
                {
                    item->setBackground(background);
                }
                tablePeers->setItem(i,j, item);
            }
            //tablePeers->horizontalHeaderItem(i)->setText(QString());
        }
        this->setGeometry(x,y,w,h);
    }
    else
    {
        vbox->addWidget(new QLabel(tr("Not Peers or bad connection!")));
        this->setLayout(vbox);
        this->setTitle(QString("Table Peers"));
        this->setGeometry(x,y,w,h);
    }
}

//void PeersTable::createMenu()
//{
//    menu = new QMenu(this);
//    QAction *hideBox2 = new QAction(this);
//    hideBox2->setText(tr("Hode Box_33333"));
//    menu->addAction(hideBox2);
//    qDebug() << "CreateMenuPeerTables";
//}

void PeersTable::changeServer(QString srv)
{
    qDebug() << "Server is " << srv;
}
