#ifndef MOVEDBOX_H
#define MOVEDBOX_H

#include <QGroupBox>
class QMenu;
class MovedBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit MovedBox(QWidget *parent = 0);
    void setOffset(int);
protected:
    void mouseMoveEvent( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPoint Position;
    QPoint OffSet;
    QMenu *menu;
    void createMenu();
signals:

public slots:

};

#endif // MOVEDBOX_H
