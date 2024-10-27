#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "duck.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    duck *d;

private:
    Ui::MainWindow *ui;
    QLabel *l;
    QWidget *labelContainer;
    QLabel *label1;
    QLabel *label2;
    int fleeingDucks;
    int successfulHits;

    void increaseSuccessfulHits();
    void increaseFleeingDucks();

    void createDuck();
    void updateLabel1();
    void updateLabel2();
};
#endif // MAINWINDOW_H
