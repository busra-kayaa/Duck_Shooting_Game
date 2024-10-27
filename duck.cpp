#include "duck.h"
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QTimer>
#include <QImage>

duck::duck(QWidget *parent) : QLabel(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &duck::animate);

    int startSpeed = 150;
    timer->start(startSpeed);
}

void duck::mousePressEvent(QMouseEvent *event) {
    timer->stop();

    QImage resim(":/res/images/vurulma.png");
    setPixmap(QPixmap::fromImage(resim));
    emit duckShot();

    QTimer::singleShot(200, this, &duck::deleteLater);
}

void duck::animate() {
    setGeometry(x(), y() + 10, width(), height());

    if (y() > parentWidget()->height()) {
        emit duckEscaped();
        deleteLater();
    }
}
