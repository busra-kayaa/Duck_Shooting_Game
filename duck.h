#ifndef DUCK_H
#define DUCK_H

#include <QLabel>
#include <QTimer>
#include<QMouseEvent>

class duck : public QLabel
{
    Q_OBJECT
public:
    explicit duck(QWidget *parent = nullptr);

private:
    QTimer *timer = new QTimer();
    void mousePressEvent(QMouseEvent*);

signals:
    void duckShot();
    void duckEscaped();

private slots:
    void animate();
};

#endif // DUCK_H
