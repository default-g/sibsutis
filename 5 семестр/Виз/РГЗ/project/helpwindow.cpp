#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    this->texts[this->ui->pushButton] = "Игра \"Мемо карточки\"\nНажмите \"Старт\", чтобы начать игру.\n Находите пары на поле путем клика по карточкам. При совпадении двух карточек они будут оставаться на поле";
    this->texts[this->ui->pushButton_2] = "ИП-014 Обухов Артем";
    connect(this->ui->pages, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handlePageSwitchOnButtonsClick(QAbstractButton*)));
    QAbstractButton* firstPagesButton = this->ui->pages->buttons().constFirst();
    firstPagesButton->setChecked(true);
    this->ui->pagesViewer->setText(this->texts[firstPagesButton]);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}


void HelpWindow::handlePageSwitchOnButtonsClick(QAbstractButton* pressedButton) {
    this->ui->pagesViewer->setText(this->texts[pressedButton]);
    pressedButton->setChecked(true);
    for (auto button : this->ui->pages->buttons()) {
        if (pressedButton != button) {
            button->setChecked(false);
        }
    }
}
