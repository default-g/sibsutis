#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsItemGroup>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    this->ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->ui->graphicsView->setSceneRect(this->frameGeometry());

    auto human = new QGraphicsItemGroup();

    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QPen outlinePen(Qt::black);
    QPen whitePen(Qt::white);


    auto borders = new QGraphicsItemGroup();

    auto upper_border = new QGraphicsLineItem(0,-25, 448, -25);
    upper_border->setPen(whitePen);

    auto bottom_border = new QGraphicsLineItem(0, 369, 448, 369);
    bottom_border->setPen(whitePen);

    auto left_border = new QGraphicsLineItem(0, -25, 0, 369);
    left_border->setPen(whitePen);

    auto right_border = new QGraphicsLineItem(448, -25, 448, 369);
    right_border->setPen(whitePen);

//    borders->addToGroup(upper_border);
//    borders->addToGroup(bottom_border);
//    borders->addToGroup(left_border);
//    borders->addToGroup(right_border);

    scene->addItem(upper_border);
    scene->addItem(bottom_border);
    scene->addItem(left_border);
    scene->addItem(right_border);

    auto head = new QGraphicsEllipseItem(5, 5, 50, 50);
    head->setBrush(whiteBrush);

    auto body = new QGraphicsLineItem(55 / 2, 55, 55 / 2, 100);
    body->setPen(whitePen);

    auto right_hand = new QGraphicsLineItem(55 / 2, 60, 55 / 2 + 25, 80);
    right_hand->setPen(whitePen);

    auto left_hand = new QGraphicsLineItem(55 / 2, 60, 55 / 2 - 25, 80);
    left_hand->setPen(whitePen);

    auto left_leg = new QGraphicsLineItem(55 / 2, 100, 55 / 2 - 25, 125);
    left_leg->setPen(whitePen);

    auto right_leg = new QGraphicsLineItem(55 / 2, 100, 55 / 2 + 25, 125);
    right_leg->setPen(whitePen);

    human->addToGroup(head);
    human->addToGroup(body);
    human->addToGroup(right_hand);
    human->addToGroup(left_hand);
    human->addToGroup(right_leg);
    human->addToGroup(left_leg);

    human->setX(10);
    human->setY(60);

    scene->addItem(human);

    auto phone = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":/images/phone.png")));
    phone->setScale(0.05);
    phone->setX(100);
    phone->setY(50);
    scene->addItem(phone);


    for (auto &item: scene->items()) {
        item->setFlags(QGraphicsItem::ItemIsMovable);
    }

    auto timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(movePhone()));
    timer->start(10);
}


void MainWindow::movePhone() {



    auto phone = this->scene->items()[0];

    if (!phone->collidingItems().empty()) {

        phone->setX(phone->pos().x() - x_direction * 2 );
        phone->setY(phone->pos().y() - y_direction * 2 );

        short minus = rand() % 2;
        this->y_direction = minus ? -1 * abs(y_direction) : abs(y_direction);
        minus = rand() % 2;
        this->x_direction = minus ? -1 * abs(x_direction) : abs(x_direction);
    }
    phone->setX(phone->pos().x() + x_direction);
    phone->setY(phone->pos().y() + y_direction);

}

MainWindow::~MainWindow()
{
    delete ui;
}

