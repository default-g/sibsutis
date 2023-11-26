#include "victorywindow.h"
#include "ui_victorywindow.h"
#include <QTime>

VictoryWindow::VictoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VictoryWindow)
{
    ui->setupUi(this);
    connect(this->ui->buttonBox, SIGNAL(accepted()), this, SLOT(addToLeaderboard()));
}


VictoryWindow::~VictoryWindow()
{
    delete ui;
}


void VictoryWindow::printData(QString data) {
    auto text = "Вы все отгадали!\n"
                    "Время: "+ data;
    this->ui->label->setText(text);
    this->time = data;
    this->show();
}


void VictoryWindow::addToLeaderboard() {
    auto name = this->ui->textEdit->toPlainText();
    name = name.trimmed();
    if (name == "") {
        return;
    }
    float time = QTime::fromString(this->time).msecsSinceStartOfDay();
    DatabaseConnection databaseConnection = DatabaseConnection(DEFAULT_DATABASE_PATH);
    databaseConnection.addRecord(name, time);
}
