#include "gulayaobukhov.h"
#include "ui_gulayaobukhov.h"
#include <QFileDialog>


GulayaObukhov::GulayaObukhov(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GulayaObukhov)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(toolButtonsClickHandler(QAbstractButton*)));
}

GulayaObukhov::~GulayaObukhov()
{
    delete ui;
}

void GulayaObukhov::recieveData(QString data) {
    // this->ui->textEdit->setText(data);
    QStringList lst = data.split("*");
    ui->textEdit->setText(lst.at(1) + "\n" + lst.at(0));
    if (lst.size() > 1) {
        QImage image(lst.at(0));
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}


void GulayaObukhov::toolButtonsClickHandler(QAbstractButton * button) {
    if (button->text() == "Reset") {
        this->ui->textEdit->clear();
        this->ui->label->clear();
    }

    if (button->text() == "Save") {
        QString filename = QFileDialog::getSaveFileName(this, "Сохранение формы");
        if (!filename.isEmpty()) {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream(&file) << this->ui->textEdit->toPlainText();
            }
            file.close();
        }
    }

    if (button->text() == "Open") {
        QString filename = QFileDialog::getOpenFileName(this, "Открыть файл");
        if (!filename.isEmpty()) {
            QFile file(filename);
            if (file.open(QIODevice::ReadOnly)) {
                QTextStream stream(&file) ;
                this->ui->textEdit->setText(stream.readAll());
                QStringList inf = this->ui->textEdit->toPlainText().split("\n");
                QImage image(inf.last());
                this->ui->label->setPixmap(QPixmap::fromImage(image));
            }


        }
    }
}
