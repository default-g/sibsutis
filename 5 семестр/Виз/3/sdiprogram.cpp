#include "sdiprogram.h"
#include "./ui_sdiprogram.h"
#include "docwindow.h"
#include <QtWidgets>

SDIProgram::SDIProgram(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SDIProgram)
{

    ui->setupUi(this);

    QMenu* pmnuFile = this->menuBar()->addMenu("&File");
    QMenu* pmnuHelp = this->menuBar()->addMenu("&Help");
    DocWindow* pdoc = new DocWindow(nullptr);


    pmnuFile->addAction("&Open...", pdoc, SLOT(slotLoad()), QKeySequence("CTRL+O"));
    pmnuFile->addAction("&Save...", pdoc, SLOT(slotSave()), QKeySequence("CTRL+S"));
    pmnuFile->addAction("&Save as...", pdoc, SLOT(slotSaveAs()));
    pmnuFile->addAction("&Color", this, SLOT(slotColorPicker()));

    pmnuHelp->addAction("&About", this, SLOT(slotAbout()));
    pmnuHelp->addAction("&Quit", this, SLOT(close()));

    this->menuBar()->addSeparator();

    this->setCentralWidget(pdoc);

    connect(pdoc, SIGNAL(changeWindowTitle(const QString&)), SLOT(slotChangeWindowTitle(const QString&)));
}

SDIProgram::~SDIProgram()
{
    delete ui;
}

void SDIProgram::slotAbout() {
    QMessageBox::about(this, "Application", "ИП-014\nОбухов Артём\nГулая Анастасия");
}

void SDIProgram::slotChangeWindowTitle(const QString& str) {
    this->setWindowTitle(str);
}

void SDIProgram::slotColorPicker() {
    auto color = QColorDialog::getColor();
    if (color.isValid()) {
        ((DocWindow *)this->centralWidget())->setTextColor(color);
    }
}
