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
    ~MovedBox();
    //void setMenuVisible(bool);
    //void initialMenu();
protected:
    void mouseMoveEvent( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *event);
    //virtual void createMenu();
    QMenu * menu;
    QAction *hideBox;
    QAction *fixedSize;
    QAction *fixedPosition;
private:
    QPoint Position;
    bool menuVisible;
private slots:
    void hide_box();
signals:

public slots:

};

#endif // MOVEDBOX_H
