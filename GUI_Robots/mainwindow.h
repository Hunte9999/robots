#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ai.h>


namespace Ui {
class MainWindow;
class MyWidget;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    robots::AI CreateRandomMap();

private slots:
    void on_pushButton_Show_clicked();

    void on_pushButton_AddRobot_clicked();

    void on_pushButton_AddModule_clicked();

    void on_pushButton_Go_clicked();

private:
    Ui::MainWindow *ui;
    robots::AI ai;
};

class MyWidget: public QWidget
{
    Q_OBJECT
private:
    const robots::env *env = nullptr;
public:
    MyWidget(QWidget * parent = 0): QWidget(parent) {}
    void setEnv(const robots::env &);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
