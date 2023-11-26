#ifndef VICTORYWINDOW_H
#define VICTORYWINDOW_H

#include <QDialog>
#include "databaseconnection.h"

namespace Ui {
class VictoryWindow;
}

class VictoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VictoryWindow(QWidget *parent = nullptr);
    ~VictoryWindow();

private:
    Ui::VictoryWindow *ui;
    QString time;

public slots:
    void printData(QString);
    void addToLeaderboard();

};


#endif // VICTORYWINDOW_H
