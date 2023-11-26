#include "docwindow.h"
#include <QFileDialog>

DocWindow::DocWindow(QWidget *pwgt): QTextEdit(pwgt) {}



void DocWindow::slotSave() {
    if (m_strFileName.isEmpty()) {
        slotSaveAs();
        return;
    }
    QFile file(m_strFileName);

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << this->toPlainText();
    }
    file.close();
    emit changeWindowTitle(m_strFileName);
}



void DocWindow::slotLoad() {
    QString str = QFileDialog::getOpenFileName();
    if (str.isEmpty()) {
        return;
    }
    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
        m_strFileName = str;
        emit changeWindowTitle(m_strFileName);
    }

}


void DocWindow::slotSaveAs() {
    QString str = QFileDialog::getSaveFileName(0, m_strFileName);
    if (!str.isEmpty()) {
        m_strFileName = str;
        slotSave();
    }
}

