#ifndef PEERSTABLE_H
#define PEERSTABLE_H
#include "movedbox.h"
class QTableWidget;


class PeersTable : public MovedBox
{
    Q_OBJECT
public:
    explicit PeersTable(QWidget *parent = 0);
    ~PeersTable();
signals:

public slots:
    void changeServer(QString);
private:
    void settingsGrid();
    QTableWidget *tablePeers;
    int x,y,w,h;
 //   QMenu *menu;
protected:
  //  void createMenu();
};

#endif // PEERSTABLE_H
