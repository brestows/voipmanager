#include "movedbox.h"
#include <QMouseEvent>
#include <QDebug>
#include <Qt>
#include <QAction>
#include <QMenu>
#include <QPoint>

#include <options.h>
MovedBox::MovedBox(QWidget *parent) : QGroupBox(parent)
{
    this->setMouseTracking(true);
    menu=new QMenu(this);
    fixedSize = new QAction(this);
    fixedSize->setText(tr("Fixed Size"));
    fixedSize->setCheckable(true);

    fixedPosition = new QAction(this);
    fixedPosition->setText(tr("Fixed Position"));
    fixedPosition->setCheckable(true);

    hideBox = new QAction(this);
    hideBox->setText(tr("Hode Box"));

    connect(hideBox,SIGNAL(triggered()),SLOT(hide_box()));
}

MovedBox::~MovedBox()
{
    Options::getInstance().writeOptions(QString("%1/positions").arg(this->objectName()), QString("%1,%2").arg(this->pos().x()).arg(this->pos().y()));
    Options::getInstance().writeOptions(QString("%1/size").arg(this->objectName()), QString("%1,%2").arg(this->size().width()).arg(this->size().height()));
}

//void MovedBox::createMenu()
//{
//    menu->addAction(fixedSize);
//    menu->addAction(fixedPosition);
//    menu->addSeparator();
//    menu->addAction(hideBox);
//    menuVisible = false;
//}

void MovedBox::hide_box()
{
    this->hide();
}

void MovedBox::mouseMoveEvent(QMouseEvent *event)
{
    switch (event->buttons())
    {
    case Qt::MidButton:
    {
        if(!fixedPosition->isChecked())
           this->move(mapToParent(event->pos() - Position));
    }break;
    case Qt::LeftButton:
    {
        QPoint glb = event->globalPos();
        glb.setY(glb.y()-14);
        int x,y,size_x,size_y;
        x = this->pos().x();
        y = this->pos().y();
        size_x = glb.x() - x;
        size_y = glb.y() - y;

        if(!fixedSize->isChecked())
        switch((int)this->cursor().shape())
        {
        case Qt::SizeFDiagCursor:
        {
            if(size_x > this->minimumSize().width())
                this->setGeometry(x,y,size_x,this->size().height());
            if(size_y > this->minimumSize().height())
                this->setGeometry(x,y,this->size().width(),size_y);
            break;
        }
        case Qt::SizeHorCursor:
        {
            if(size_x >this->minimumSize().width())
                this->setGeometry(x,y,size_x,this->size().height());
            break;
        }
        case Qt::SizeVerCursor:
        {
            if(size_y >this->minimumSize().height())
                this->setGeometry(x,y,this->size().width(),size_y);
            break;
        }
        default:break;
        }
    }break;
    default:
    {
        if(!fixedSize->isChecked())
        {
            int x,y;
            QPoint glb = mapToParent(event->globalPos());
            QPoint tpm = this->pos();
            tpm.setX(tpm.x()+this->size().width());
            tpm.setY(tpm.y()+this->size().height());
            QPoint lcl = mapToGlobal(tpm);
            QPoint angleResize(5,5);
            QPoint tmp = lcl-glb;
            x =  tmp.x();
            y = tmp.y();
           // qDebug() << x << " " << y;
            if(x < angleResize.x() && y < angleResize.y())
                this->setCursor(Qt::SizeFDiagCursor);
            else if (x < angleResize.x() )
                this->setCursor(Qt::SizeHorCursor);
            else if (y < angleResize.y() )
                this->setCursor(Qt::SizeVerCursor);
            else
                this->setCursor(Qt::ArrowCursor);
            //qDebug()<< lcl - glb;
        }
    }break;
    }
    event->accept();
}

void MovedBox::mousePressEvent(QMouseEvent *event)
{
    switch (event->buttons())
    {
    case Qt::MidButton:
    {
        Position = event->pos();
        this->setCursor(Qt::SizeAllCursor);
    }break;
    case Qt::RightButton:
    {
        menu->exec(mapToGlobal(event->pos()));
    }break;
    }
    event->accept();

}

void MovedBox::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    event->accept();
}

//void MovedBox::setMenuVisible(bool vis)
//{
//    menuVisible = vis;
//}

//void MovedBox::initialMenu()
//{
//     createMenu();
//}
