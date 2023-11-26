#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QDialog>

namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QDialog
{
    Q_OBJECT

public:
    explicit LeaderBoard(QWidget *parent = nullptr);
    ~LeaderBoard();

private:
    Ui::LeaderBoard *ui;
};

#endif // LEADERBOARD_H
