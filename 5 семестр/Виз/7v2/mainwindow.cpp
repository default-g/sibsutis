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

    auto palm = new QGraphicsItemGroup();

    QBrush greenBrush(Qt::darkGreen);
    QPen outlinePen(Qt::white);
    QPen blackPen(Qt::black);
    QPen whitePen(Qt::white);

    QBrush brownBrush(QColor(97, 66, 13));



    auto borders = new QGraphicsItemGroup();

    auto upper_border = new QGraphicsLineItem(0,-25, 448, -25);
    upper_border->setPen(whitePen);

    auto bottom_border = new QGraphicsLineItem(0, 369, 448, 369);
    bottom_border->setPen(whitePen);

    auto left_border = new QGraphicsLineItem(0, -25, 0, 369);
    left_border->setPen(whitePen);

    auto right_border = new QGraphicsLineItem(448, -25, 448, 369);
    right_border->setPen(whitePen);

    scene->addItem(upper_border);
    scene->addItem(bottom_border);
    scene->addItem(left_border);
    scene->addItem(right_border);

    auto trunk = new QGraphicsPolygonItem();

    QPolygonF polygon;

    polygon.append(QPointF(100, 200));
    polygon.append(QPointF(150, 200));
    polygon.append(QPointF(125, 50));
    trunk->setPolygon(polygon);
    trunk->setBrush(brownBrush);
    trunk->boundingRegion(QTransform());

    QPolygonF polygon_for_first_leaf;

    auto first_leaf = new QGraphicsPolygonItem();
    polygon_for_first_leaf.append(QPointF(125, 50));
    polygon_for_first_leaf.append(QPointF(200, 100));
    polygon_for_first_leaf.append(QPointF(160, 40));
    first_leaf->setPolygon(polygon_for_first_leaf);
    first_leaf->setBrush(greenBrush);

    QPolygonF polygon_for_second_leaf;

    auto second_leaf = new QGraphicsPolygonItem();
    polygon_for_second_leaf.append(QPointF(125, 50));
    polygon_for_second_leaf.append(QPointF(175, 25));
    polygon_for_second_leaf.append(QPointF(225, 40));
    second_leaf->setPolygon(polygon_for_second_leaf);
    second_leaf->setBrush(greenBrush);

    QPolygonF polygon_for_third_leaf;

    auto third_leaf = new QGraphicsPolygonItem();
    polygon_for_third_leaf.append(QPointF(90, 40));
    polygon_for_third_leaf.append(QPointF(50, 100));
    polygon_for_third_leaf.append(QPointF(125, 50));
    third_leaf->setPolygon(polygon_for_third_leaf);
    third_leaf->setBrush(greenBrush);

    QPolygonF polygon_for_fourth_leaf;

    auto fourth_leaf = new QGraphicsPolygonItem();
    polygon_for_fourth_leaf.append(QPointF(25, 40));
    polygon_for_fourth_leaf.append(QPointF(75, 25));
    polygon_for_fourth_leaf.append(QPointF(125, 50));
    fourth_leaf->setPolygon(polygon_for_fourth_leaf);
    fourth_leaf->setBrush(greenBrush);

    palm->addToGroup(first_leaf);
    palm->addToGroup(second_leaf);
    palm->addToGroup(third_leaf);
    palm->addToGroup(fourth_leaf);
    palm->addToGroup(trunk);

    palm->setX(10);
    palm->setY(60);

    scene->addItem(palm);

    auto phone = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":/monke.png")));
    phone->setScale(0.25);

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

    if (!phone->collidingItems(Qt::IntersectsItemShape).empty()) {

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

