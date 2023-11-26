#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QThread>
#include <QButtonGroup>
#include <QMessageBox>
#include "helpwindow.h"
#include "leaderboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->victoryWindow = new VictoryWindow();
    connect(this->ui->start, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(this->ui->mainField, SIGNAL(buttonReleased(QAbstractButton *)),this, SLOT(plateClickHandler(QAbstractButton *)));
    connect(this->ui->help, SIGNAL(triggered()), this, SLOT(showHelpWindow()));
    connect(this->ui->leaderboard, SIGNAL(triggered()), this, SLOT(showLeaderBoard()));
    connect(this, SIGNAL(showVictoryWindow(QString)), this->victoryWindow, SLOT(printData(QString)));

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::shuffle() {
    std::random_device rd;
//    std::shuffle(icons.begin(), icons.end(), rd);
    int i = 0;
    for(auto button : this->ui->mainField->buttons()) {
         iconsPairs[button] = icons[i++];
    }
}


void MainWindow::showTime() {
    QTime time = QTime::fromString(this->ui->timer->text());
    time = time.addSecs(1);
    this->ui->timer->setText(time.toString("HH:mm:ss"));
}


void MainWindow::updateMatchesCounter(unsigned int newCounter) {
    this->ui->matchesCounter->setText(QString::fromStdString("Отгадано: " + std::to_string(newCounter)));
}


void MainWindow::plateClickHandler(QAbstractButton* button) {

    button->setText(iconsPairs[button]);
    button->repaint();

    if (button == this->firstClickedButton || button == this->secondClickedButton) {
        return;
    }

    if (!this->firstClickedButton) {
        this->firstClickedButton = button;
        return;
    }

    if (!this->secondClickedButton) {
        this->secondClickedButton = button;
    }

    if (this->firstClickedButton->text() == this->secondClickedButton->text()) {
        this->updateMatchesCounter(++this->matchesCount);
        this->firstClickedButton->setEnabled(false);
        this->secondClickedButton->setEnabled(false);
    } else {
        QCoreApplication::processEvents();
        QThread::sleep(1);
        this->firstClickedButton->setText("");
        this->secondClickedButton->setText("");
    }

    if (this->matchesCount >= this->maxMatchesCount) {
        this->timer->stop();
        this->displayWinningDialog();
        this->resetGame();
    }

    this->firstClickedButton = nullptr;
    this->secondClickedButton = nullptr;
}


void MainWindow::displayWinningDialog() {
    auto data = this->ui->timer->text();
    emit showVictoryWindow(data);
}


void MainWindow::resetGame() {
    this->matchesCount = 0;
    this->timer->stop();
    this->ui->timer->hide();
    this->ui->matchesCounter->hide();
    this->ui->start->show();
    for (auto button : this->ui->mainField->buttons()) {
        button->setText("");
        button->setEnabled(false);
    }
}


void MainWindow::startGame() {
    this->shuffle();
    this->timer->start(1000);
    this->ui->timer->setText("00:00:00");
    for (auto button : this->ui->mainField->buttons()) {
        button->setEnabled(true);
    }
    this->matchesCount = 0;
    this->updateMatchesCounter(this->matchesCount);
    this->ui->timer->show();
    this->ui->matchesCounter->show();
    this->ui->start->hide();
}


void MainWindow::showHelpWindow() {
    HelpWindow *helpWindow = new HelpWindow();
    helpWindow->show();
    this->resetGame();
}


void MainWindow::showLeaderBoard() {
    auto leaderBoard = new LeaderBoard();
    leaderBoard->show();
    this->resetGame();
}

