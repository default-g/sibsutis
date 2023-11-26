#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene *scene;
    float x_direction = 1;
    float y_direction = 1;

private:
    Ui::MainWindow *ui;
public slots:
    void movePhone();
};
#endif // MAINWINDOW_H
