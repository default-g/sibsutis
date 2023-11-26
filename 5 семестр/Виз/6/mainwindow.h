#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gulayaobukhov.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GulayaObukhov* myform;
signals:
    void sendData(QString);
private slots:
    void onButtonSend();
    void uploadButtonHandler();

};
#endif // MAINWINDOW_H
