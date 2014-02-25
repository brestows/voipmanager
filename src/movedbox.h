#ifndef MOVEDBOX_H
#define MOVEDBOX_H

#include <QGroupBox>
class QMenu;
class QAction;
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
    QAction *hideBox;
    QAction *fixedSize;
    QAction *fixedPosition;
    void createMenu();
    void initActions();
private slots:
    void hide_box();
signals:

public slots:

};

#endif // MOVEDBOX_H
