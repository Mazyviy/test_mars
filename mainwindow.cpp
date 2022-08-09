#include "mainwindow.h"
#include "ui_mainwindow.h"

extern bool flagTrajectoryCat, flagTrajectoryWumpus, flagTrajectoryGhost;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btnRunCat->setIcon(QIcon(QPixmap(":resource/images/blue.png")));
    ui->btnRunCat->setIconSize(QSize(20,20));
    ui->btnRunWumpus->setIcon(QIcon(QPixmap(":resource/images/green.png")));
    ui->btnRunWumpus->setIconSize(QSize(20,20));
    ui->btnRunGhost->setIcon(QIcon(QPixmap(":resource/images/orange.png")));
    ui->btnRunGhost->setIconSize(QSize(20,20));
    ui->label->setText("◇ Веревочка с колокольчиком\n✧ Детектор протоплазмы");
    ui->label->setFont(QFont("times",12));
    ui->label->adjustSize();

    field=new Field();
    connect(ui->btnShuffleTraps,SIGNAL(clicked()),field,SLOT(UpdateTrapGeneration()));
    connect(ui->btnRunCat,SIGNAL(clicked()),field,SLOT(UpdateTrajectoryCat()));
    connect(ui->btnRunWumpus,SIGNAL(clicked()),field,SLOT(UpdateTrajectoryWumpus()));
    connect(ui->btnRunGhost,SIGNAL(clicked()),field,SLOT(UpdateTrajectoryGhost()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Кнопка "Стереть траектории"
void MainWindow::on_btnDelTrajectories_clicked()
{
    flagTrajectoryCat=false;
    flagTrajectoryWumpus=false;
    flagTrajectoryGhost=false;
    update();
}

// Кнопка "Перетасовать ловушки"
void MainWindow::on_btnShuffleTraps_clicked()
{
     flagTrajectoryCat=false;
     flagTrajectoryWumpus=false;
     flagTrajectoryGhost=false;
     update();
}

//Кнопка "Запустить кошку"
void MainWindow::on_btnRunCat_clicked()
{
    flagTrajectoryCat=true;
    update();
}

//Кнопка "Запустить вампуса"
void MainWindow::on_btnRunWumpus_clicked()
{
    flagTrajectoryWumpus=true;
    update();
}

//Кнопка "Запустить призрака"
void MainWindow::on_btnRunGhost_clicked()
{
    flagTrajectoryGhost=true;
    update();
}


