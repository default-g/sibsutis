#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>
#include <QMap>
#include <QAbstractButton>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

private:
    QMap <QAbstractButton *, QString> texts;
    Ui::HelpWindow *ui;
private slots:
    void handlePageSwitchOnButtonsClick(QAbstractButton *);
};

#endif // HELPWINDOW_H
