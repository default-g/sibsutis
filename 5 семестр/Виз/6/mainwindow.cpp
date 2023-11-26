#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->myform = new GulayaObukhov();
    connect(ui->add, SIGNAL(clicked()), myform, SLOT(show()));
    connect(ui->add, SIGNAL(clicked()), this, SLOT(onButtonSend()));
    connect(ui->upload, SIGNAL(clicked()), this, SLOT(uploadButtonHandler()));
    connect(this, SIGNAL(sendData(QString)), myform, SLOT(recieveData(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::uploadButtonHandler() {
    QString filename = QFileDialog::getOpenFileName(nullptr, "Выберите изображение");
    ui->filePath->setText(filename);
    QImage image(filename);
    ui->image->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::onButtonSend() {
    QString out = ui->filePath->text() + "*" +ui->name->text()  +" \n" + ui->job->text() + "\n" + ui->birth_date->text() + "\n" + ui->address->text();
    if (ui->female->isChecked()) {
        out += "\nпол: Ж";
    } else {
        out += "\nпол: М";
    }
    emit sendData(out);
}
