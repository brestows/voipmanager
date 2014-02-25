#ifndef MASTER_H
#define MASTER_H

#include <QWizard>

class Master : public QWizard
{
    Q_OBJECT
public:
    Master(QWidget *parent = 0);

    void accept();

};

#endif // MASTER_H
