#ifndef SDIPROGRAM_H
#define SDIPROGRAM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SDIProgram; }
QT_END_NAMESPACE

class SDIProgram : public QMainWindow
{
    Q_OBJECT

public:
    SDIProgram(QWidget *parent = nullptr);
    ~SDIProgram();
public slots:
    void slotAbout();
    void slotChangeWindowTitle(const QString&);
    void slotColorPicker();

private:
    Ui::SDIProgram *ui;
};
#endif // SDIPROGRAM_H
