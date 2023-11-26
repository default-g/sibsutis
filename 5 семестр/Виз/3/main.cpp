#include "sdiprogram.h"

#include <QApplication>
#include <QtWidgets>
#include <QSplashScreen>



void loadModules(QSplashScreen* psplash) {
    QElapsedTimer time;
    time.start();
    for (int i = 0; i < 100; ) {
        if (time.elapsed() > 40) {
            time.start();
            i++;
        }

        psplash->showMessage("Load modules: " + QString::number(i) + "%", Qt::AlignCenter | Qt::AlignCenter, Qt::white);

        qApp->processEvents();
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap("/Users/defaultid/Google\ Drive/учоба/5\ семестр/Виз/3/s.jpeg"));
    splash.show();
    SDIProgram w;
    loadModules(&splash);
    splash.finish(&w);
    w.show();
    return a.exec();
}
