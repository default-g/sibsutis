#include "mainwindow.h"

#include <QApplication>
#include "StartDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog startDialog;
    startDialog.show();

    return a.exec();
}
