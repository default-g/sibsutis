#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>>
#include <QGridLayout>>

class QLineEdit;

class InputDialog: public QDialog
{
    Q_OBJECT;
private:
    QLineEdit* m_ptxtFirstName;
    QLineEdit* m_ptxtLastName;
public:
    InputDialog(QWidget* pwgt = nullptr): QDialog(pwgt) {
        this->m_ptxtFirstName = new QLineEdit();
        this->m_ptxtLastName = new QLineEdit();

        QLabel* plblFirstName = new QLabel("&Имя");
        QLabel* plblLastName = new QLabel("&Фамилия");

        plblFirstName->setBuddy(this->m_ptxtFirstName);
        plblLastName->setBuddy(this->m_ptxtLastName);

        QPushButton* pcmdOk = new QPushButton("&Ok");
        QPushButton* pcmdCancel = new QPushButton("&Cancel");

        connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
        connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

        QGridLayout* ptopLayout = new QGridLayout();
        ptopLayout->addWidget(plblFirstName, 0, 0);
        ptopLayout->addWidget(plblLastName, 1, 0);
        ptopLayout->addWidget(m_ptxtFirstName, 0, 1);
        ptopLayout->addWidget(m_ptxtLastName, 1, 1);
        ptopLayout->addWidget(pcmdOk, 2, 0);
        ptopLayout->addWidget(pcmdCancel, 2, 1);

        this->setLayout(ptopLayout);





    }

    const QString firstName() {
        return this->m_ptxtFirstName->text();
    };

    const QString lastName() {
        return this->m_ptxtLastName->text();
    }
};


#endif // INPUTDIALOG_H
