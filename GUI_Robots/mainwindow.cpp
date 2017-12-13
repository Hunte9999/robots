#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ai(CreateRandomMap())
{
    int a, b;
    ai.getEn().getRazm(a, b);
    //ui->spinBox_x->setMaximum(a);
    //ui->spinBox_y->setMaximum(b);

    ui->setupUi(this);
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    if( env == nullptr ){
        return;
    }

    int shag = 32, a, b;
    QImage wall(":/resources/images/tile_wall.png");
    QImage wall_close(":/resources/images/wall_close.jpg");
    QImage grass(":/resources/images/tile_grass.png");
    QImage grass_close(":/resources/images/grass_close.jpg");
    QImage baserobot(":/resources/images/baserobot.jpg");
    QImage movingrobot(":/resources/images/movingrobot.jpg");
    QImage managerrobot(":/resources/images/managerrobot.jpg");
    QImage movmanagerobot(":/resources/images/movmanagerobot.jpg");
    QImage ti(":/resources/images/fire1.png");
    QImage ti_close(":/resources/images/ti_close.jpg");

    env->getRazm(a, b);


    QPainter painter(this);
    for(int i = 0; i < a; ++i){
        for(int j = 0; j < b; ++j){
            switch(env->getPlace(i, j)->retType()){
            case 0:
                if(env->getPlace(i, j)->getSost() == robots::CLOSE){
                    painter.drawImage(i* shag, j*shag, grass_close);
                }
                else{
                    painter.drawImage(i* shag, j* shag, grass);
                }
                break;
            case 1:
                if(env->getPlace(i, j)->getSost() == robots::CLOSE){
                    painter.drawImage(i* shag, j* shag, ti_close);
                }
                else{
                    painter.drawImage(i* shag, j* shag, ti);
                }
                break;
            case 2:
                if(env->getPlace(i, j)->getSost() == robots::CLOSE){
                    painter.drawImage(i* shag, j* shag, wall_close);
                }
                else{
                    painter.drawImage(i* shag, j* shag, wall);
                }
                break;
            case 3:
                painter.drawImage(i* shag, j* shag, baserobot);
                break;
            case 4:
                painter.drawImage(i* shag, j* shag, movingrobot);
                break;
            case 5:
                painter.drawImage(i* shag, j* shag, managerrobot);
                break;
            case 6:
                painter.drawImage(i* shag, j* shag, movmanagerobot);
                break;
            }
        }
    }
    painter.end();
}

void MyWidget::setEnv(const robots::env &en)
{
    env = &en;
}

robots::AI MainWindow::CreateRandomMap()
{
    int a = rand()%20 + 5, b = rand()%20 + 5, numobst = rand()%10+1, numti = rand()%5 + 1, x, y;
    robots::env en(a, b);
    robots::AI res(en);
    bool da;
    for (int i = 0; i < numobst; ++i){
        da = false;
        do{
            x = rand()%a;
            y = rand()%b;
            //if(res.getEn().getPlace(x, y)->retType() == 0){
                res.addDiffPlace(x, y, 0);
                da = true;
            //}
        }while(!da);
    }
    for (int i = 0; i < numti; ++i){
        da = false;
        do{
            x = rand()%a;
            y = rand()%b;
            //if(res.getEn().getPlace(x, y)->retType() == 0){
                res.addDiffPlace(x, y, 1);
                da = true;
            //}
        }while(!da);
    }
    return res;
}

void MainWindow::on_pushButton_Show_clicked()
{
    ui->widget->setEnv(ai.getEn());
    repaint();
    update();
}

void MainWindow::on_pushButton_AddRobot_clicked()
{
    int type, x, y, maxnmod, velocity = 0;

    if(ui->radioButton_component->isChecked()){
        type = 0;
    } else if(ui->radioButton_moving->isChecked()){
        type = 1;
    } else if(ui->radioButton_managing->isChecked()){
        type = 2;
    } else if(ui->radioButton_movman->isChecked()){
        type = 3;
    } else return;

    maxnmod = ui->spinBox_maxnummod->value();
    x = ui->spinBox_x->value();
    y = ui->spinBox_y->value();
    velocity = ui->spinBox_velocity->value();

    ai.addComponent(x, y, maxnmod, type, velocity);

    ui->spinBox_nofRob->setMaximum(ui->spinBox_nofRob->maximum() + 1);
    on_pushButton_Show_clicked();
    //update();
}

void MainWindow::on_pushButton_AddModule_clicked()
{
    int n, type, energyuse, cost, energylevel = 0, maxnumb = 0, radius = 0, angle = 0;

    n = ui->spinBox_nofRob->value();

    if(ui->radioButton_generator->isChecked()){
        type = 1;
    } else if(ui->radioButton_sensor->isChecked()){
        type = 2;
        radius = 1;
    } else if(ui->radioButton_manager->isChecked()){
        type = 3;
        radius = 2;
        maxnumb = 2;
    } else return;

    energyuse = 1;
    cost = 1;

    ai.addModule(n, type, energyuse, cost, energylevel, maxnumb, radius, angle);
    on_pushButton_Show_clicked();
}

void MainWindow::on_pushButton_Go_clicked()
{
    int n = ui->spinBox->value();
    for(int i = 0; i < n; ++i){
        ai.start(1);
        on_pushButton_Show_clicked();
        usleep(1000*1000);
    }
    /*ai.start(n);
    ui->widget->setEnv(ai.getEn());
    repaint();
    update();*/
    /*for (int i = 0; i < n; ++i){
        ai.start(1);
        //ui->widget->setEnv(ai.getEn());
        //repaint();
        update();
//    }*/
}
