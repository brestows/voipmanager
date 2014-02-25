#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class QListWidgetItem;
class QSettings;

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    void loadSettings();
    void saveSettings();
    void saveItemSettings();
    void readItemSettings();
    ~Settings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Settings *ui;
    QSettings *options;
    void settingsForm();

private slots:
    void changeSection(QListWidgetItem*,QListWidgetItem*);
};

#endif // SETTINGS_H
