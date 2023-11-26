#ifndef DOCWINDOW_H
#define DOCWINDOW_H

#include <QTextEdit>
#include <QObject>

class DocWindow : public QTextEdit
{
    Q_OBJECT
public:
    DocWindow(QWidget *);

private:
    QString m_strFileName;

signals:
    void changeWindowTitle(const QString&);

public slots:
    void slotLoad();
    void slotSave();
    void slotSaveAs();

};

#endif // DOCWINDOW_H
