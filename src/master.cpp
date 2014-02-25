#include "master.h"

Master::Master(QWidget *parent) :    QWizard(parent)
{

    setWindowTitle(tr("Test Wizaed Master"));
}

void Master::accept()
{

    QDialog::accept();
}
