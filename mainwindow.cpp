#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fleeingDucks(0)
    , successfulHits(0)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    l = new QLabel(this);
    l->setScaledContents(true);
    l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Otomatik boyutlandırma

    QImage image2(":/res/images/arkaPlan.png");
    l->setPixmap(QPixmap::fromImage(image2));

    mainLayout->addWidget(l);

    labelContainer = new QWidget(this);
    QVBoxLayout *labelLayout = new QVBoxLayout(labelContainer);

    label1 = new QLabel(this);
    label1->setText("Vurulan Ördek: \n0");
    label1->setStyleSheet("QLabel { color: #00FF00; border: 0px; font-weight: bold; }");
    label1->setFont(QFont("Arial", 10));

    label2 = new QLabel(this);
    label2->setStyleSheet("QLabel { color: #FF0000; border: 0px; font-weight: bold; }");
    label2->setText("Kaçan Ördek: \n0");
    label2->setFont(QFont("Arial", 10));

    labelLayout->addWidget(label1);
    labelLayout->addWidget(label2);
    labelContainer->setLayout(labelLayout);

    labelContainer->setMinimumWidth(190);
    labelContainer->setMinimumHeight(100);

    mainLayout->addWidget(labelContainer);

    QTimer *create = new QTimer(this);
    connect(create, &QTimer::timeout, this, &MainWindow::createDuck);
    create->start(500);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    QSize size = event->size(); // Yeni pencere boyutu

    QFont font1 = label1->font();
    font1.setPointSize(size.height() / 50);
    label1->setFont(font1);

    QFont font2 = label2->font();
    font2.setPointSize(size.height() / 50);
    label2->setFont(font2);
}

void MainWindow::createDuck() {
    int backgroundWidth = l->width();
    int minX = 0;
    int maxX = backgroundWidth;
    int x = QRandomGenerator::global()->bounded(minX, maxX);

    duck *d = new duck(l);
    d->setScaledContents(true);

    int duckSize = std::min(width() * 0.03, height() * 0.04);
    d->setGeometry(x, 0, duckSize, duckSize);

    QImage image(":/res/images/ordek.png");
    d->setPixmap(QPixmap::fromImage(image));
    d->show();

    connect(d, &duck::duckShot, this, &MainWindow::increaseSuccessfulHits);
    connect(d, &duck::duckEscaped, this, &MainWindow::increaseFleeingDucks);
}

void MainWindow::increaseSuccessfulHits() {
    successfulHits++;
    updateLabel1();
}

void MainWindow::increaseFleeingDucks() {
    fleeingDucks++;
    updateLabel2();
}

void MainWindow::updateLabel1() {
    label1->setText("Vurulan Ördek: \n" + QString::number(successfulHits));
}

void MainWindow::updateLabel2() {
    label2->setText("Kaçan Ördek: \n" + QString::number(fleeingDucks));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_F11) { // F11 tuşuna basarak tam ekrana geçilir.
        if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
    }
    QMainWindow::keyPressEvent(event);
}
