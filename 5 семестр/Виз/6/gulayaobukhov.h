#ifndef GULAYAOBUKHOV_H
#define GULAYAOBUKHOV_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class GulayaObukhov;
}

class GulayaObukhov : public QWidget
{
    Q_OBJECT

public:
    explicit GulayaObukhov(QWidget *parent = nullptr);
    ~GulayaObukhov();

private:
    Ui::GulayaObukhov *ui;

public slots:
    void recieveData(QString);
    void toolButtonsClickHandler(QAbstractButton*);
};

#endif // GULAYAOBUKHOV_H
