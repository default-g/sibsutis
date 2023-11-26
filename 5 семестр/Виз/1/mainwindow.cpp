#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "authors.h"
#include <QFileDialog>
#include <QTextDocumentWriter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    connect(ui->action, SIGNAL(triggered()), this, SLOT(about()));

    QAction *pactOpen = new QAction("file open action", nullptr);
    pactOpen->setText("&Открыть");
    pactOpen->setShortcut(QKeySequence("CTRL+O"));
    pactOpen->setToolTip("Открытие документа");
    pactOpen->setStatusTip("Открыть файл");
    pactOpen->setWhatsThis("Открыть файл");
    connect(pactOpen, SIGNAL(triggered()), SLOT(slot_open()));

    QAction *pactSave = new QAction("file save action", nullptr);
    pactSave->setText("&Сохранить");
    pactSave->setShortcut(QKeySequence("CTRL+S"));
    pactSave->setToolTip("Сохранение документа");
    pactSave->setStatusTip("Сохранить файл");
    pactSave->setWhatsThis("Сохранить файл");
    connect(pactSave, SIGNAL(triggered()), SLOT(slot_save()));

    QAction *pactClear = new QAction("clear action", nullptr);
    pactClear->setText("&Очистить");
    pactClear->setShortcut(QKeySequence("CTRL+N"));
    pactClear->setToolTip("Очистить");
    pactClear->setStatusTip("Очистить");
    pactClear->setWhatsThis("Очистить");
    connect(pactClear, SIGNAL(triggered()), SLOT(slot_clear()));

    QMenu *pmnuFile = new QMenu("&Файл");
    pmnuFile->addAction(pactOpen);
    pmnuFile->addAction(pactSave);
    pmnuFile->addAction(pactClear);
    this->menuBar()->addMenu(pmnuFile);

    this->ui->menu->addAction(pactOpen);
    this->ui->menu->addAction(pactSave);
    this->ui->menu->addAction(pactClear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about() {
    auto diolog_window = new Authors();
    diolog_window->show();
}

void MainWindow::slot_open() {
    QString filename = QFileDialog::getOpenFileName(nullptr, "Открыть файл");
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->textEdit->setPlainText(file.readAll());
    }
}

void MainWindow::slot_save() {
    QString filename = QFileDialog::getSaveFileName(nullptr, "Сохранить файл");
    QTextDocumentWriter *writer = new QTextDocumentWriter();
    writer->setFileName(filename);
    writer->write(ui->textEdit->document());
    delete writer;
}

void MainWindow::slot_clear() {
    ui->textEdit->clear();
}
