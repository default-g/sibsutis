#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <iostream>
#include <algorithm>
#include <random>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include "victorywindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMap <QAbstractButton *, QString> iconsPairs;

    QAbstractButton *firstClickedButton = nullptr;
    QAbstractButton *secondClickedButton = nullptr;

    QList <QString> icons = {
        "水", "水",
        "天", "天",
        "要", "要",
        "睛", "睛",
        "北", "北",
        "四", "四",
        "考", "考",
        "背", "背",
    };

    unsigned int matchesCount = 0;
    const unsigned int maxMatchesCount = icons.size() / 2;

    void updateMatchesCounter(unsigned int);
    void resetGame();
    void displayWinningDialog();

private slots:
    void showTime();
    void startGame();
    void plateClickHandler(QAbstractButton *);
    void showHelpWindow();
    void showLeaderBoard();

private:
    Ui::MainWindow *ui;
    void shuffle();
    QTimer *timer = new QTimer();
    VictoryWindow *victoryWindow;

signals:
    void showVictoryWindow(QString);
};
#endif // MAINWINDOW_H
