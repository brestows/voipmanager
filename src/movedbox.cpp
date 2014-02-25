#include "movedbox.h"
#include <QMouseEvent>
#include <QDebug>
#include <Qt>
#include <QAction>
#include <QMenu>
#include <QPoint>

MovedBox::MovedBox(QWidget *parent) : QGroupBox(parent)
{
    this->setMouseTracking(true);
    createMenu();
}


void MovedBox::createMenu()
{
    menu=new QMenu(this);
    initActions();
    menu->addAction(fixedSize);
    menu->addAction(fixedPosition);
    menu->addSeparator();
    menu->addAction(hideBox);

}

void MovedBox::initActions()
{
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
            this->move(event->globalPos() - Position);
    }break;
    case Qt::LeftButton:
    {
        QPoint glb = event->globalPos() - OffSet;
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
            if(size_x >this->minimumSize().width())
                this->setGeometry(x,y,size_x,this->size().height());
            if(size_y >this->minimumSize().height())
                this->setGeometry(x,y,this->size().width(),size_y);
            break;
        }
        case Qt::SizeHorCursor:
        {
            qDebug() << "Hor";
            if(size_x >this->minimumSize().width())
                this->setGeometry(x,y,size_x,this->size().height());
            break;
        }
        case Qt::SizeVerCursor:
        {
            qDebug() << "Ver";
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
            QPoint glb = mapToGlobal(event->globalPos());
            QPoint tpm = this->pos() + OffSet;
            tpm.setX(tpm.x()+this->size().width());
            tpm.setY(tpm.y()+this->size().height());
            QPoint lcl = mapToGlobal(tpm);
            QPoint angleResize(10,10);
            QPoint tmp = lcl-glb;
            if(tmp.x() < angleResize.x() && tmp.y() < angleResize.y())
                this->setCursor(Qt::SizeFDiagCursor);
            else if (tmp.x() < angleResize.x() )
                this->setCursor(Qt::SizeHorCursor);
            else if (tmp.y() < angleResize.y() )
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
        Position = event->pos()+OffSet;
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

void MovedBox::setOffset(int y)
{
    OffSet.setY(y-13);
}
