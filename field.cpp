#include "field.h"

QVector<QVector<int>> traps(5,QVector<int>(5));
QVector<QVector<int>> trajectoryCat, trajectoryGhost, trajectoryWumpus;
bool flagTrajectoryCat, flagTrajectoryWumpus, flagTrajectoryGhost;

Field::Field(QWidget *parent) : QWidget(parent)
{
    UpdateTrapGeneration();
}

// Отрисовывает все на виджете
void Field::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor("black"), 1, Qt::SolidLine, Qt::FlatCap));
    painter.setFont(QFont("times", 24));
    float height_line=0, width_line=0, height_text=20, width_text=20;
    // Линии поля
    for (int i=0; i<4; ++i) {
        painter.drawLine(QLine(0, height_line, Field::width(), height_line));
        height_line+=Field::height()/3+0.6;
        painter.drawLine(QLine(width_line, 0, width_line, Field::height()));
        width_line+=Field::width()/3+0.6;
    }
    // Ловушки поля
    for (int i=1; i<traps.size()-1; ++i) {
        height_text=45;
        for (int j=1; j<traps[0].size()-1; ++j) {
            QString trap;
            if(traps[i][j]==0) trap="";
            else if(traps[i][j]==1) trap="◇";
            else if(traps[i][j]==2) trap="✧";
            painter.drawText(QPoint(width_text, height_text), trap);
            height_text+=Field::height()/3;
        }
        width_text+=Field::width()/3;
    }

    QVector<QVector<int>> triggered_traps(5, QVector<int>(5));
    int weight_point_end, height_point_end, weight_point_begin, height_point_begin;

    // Траектория кошки
    if(flagTrajectoryCat){
        QVector<QVector<int>> triggered_trapsCat(5, QVector<int>(5));
        weight_point_end=Field::width()/3+Field::width()/6+5+rand()%10;
        height_point_end=Field::height()/3+Field::height()/6+5+rand()%10;
        weight_point_begin=weight_point_end;
        height_point_begin=height_point_end;
        painter.setPen(QPen(QColor("blue"), 8, Qt::SolidLine, Qt::FlatCap));
        painter.drawPoint(weight_point_begin, height_point_begin);

        painter.setPen(QPen(QColor("blue"), 5, Qt::SolidLine, Qt::FlatCap));
        for (int i=0; i<trajectoryCat.size(); ++i) {
            if (!trajectoryCat.size()-1){
                if(traps[trajectoryCat[i][0]][trajectoryCat[i][1]]==2) triggered_trapsCat[trajectoryCat[i][0]][trajectoryCat[i][1]]=3;
                else if(traps[trajectoryCat[i][0]][trajectoryCat[i][1]]==1) triggered_trapsCat[trajectoryCat[i][0]][trajectoryCat[i][1]]=3;
                else triggered_trapsCat[trajectoryCat[i][0]][trajectoryCat[i][1]]=0;
            }

            if(i!=0){
                if(trajectoryCat[i][0]<trajectoryCat[i-1][0]) weight_point_end-=Field::width()/3;
                else if(trajectoryCat[i][0]>trajectoryCat[i-1][0]) weight_point_end+=Field::width()/3;
                if(trajectoryCat[i][1]<trajectoryCat[i-1][1]) height_point_end-=Field::height()/3;
                else if(trajectoryCat[i][1]>trajectoryCat[i-1][1]) height_point_end+=Field::height()/3;

                if(weight_point_end<0) weight_point_end=0;
                else if(weight_point_end>Field::width()) weight_point_end=Field::width();
                if(height_point_end<0) height_point_end=0;
                else if(height_point_end>Field::height()) height_point_end=Field::height();

                painter.drawLine(QLine(weight_point_begin, height_point_begin, weight_point_end, height_point_end));
                weight_point_begin=weight_point_end;
                height_point_begin=height_point_end;
            }
        }

        for (int i=0; i<triggered_traps.size(); ++i) {
            for (int j=0; j<triggered_traps[0].size(); ++j) {
                triggered_traps[i][j]+=triggered_trapsCat[i][j];
            }
        }
    }

    // Траектория вампуса
    if(flagTrajectoryWumpus){
        QVector<QVector<int>> triggered_trapsWumpus(5, QVector<int>(5));
        weight_point_end=Field::width()/3+Field::width()/6+5+rand()%10;
        height_point_end=Field::height()/3+Field::height()/6+5+rand()%10;
        weight_point_begin=weight_point_end;
        height_point_begin=height_point_end;
        painter.setPen(QPen(QColor("green"), 8, Qt::SolidLine, Qt::FlatCap));
        painter.drawPoint(weight_point_begin, height_point_begin);

        painter.setPen(QPen(QColor("green"), 5, Qt::SolidLine, Qt::FlatCap));
        for (int i=0; i<trajectoryWumpus.size(); ++i) {
            if (!trajectoryWumpus.size()-1){
                if(traps[trajectoryWumpus[i][0]][trajectoryWumpus[i][1]]==2) triggered_trapsWumpus[trajectoryWumpus[i][0]][trajectoryWumpus[i][1]]=0;
                else if(traps[trajectoryWumpus[i][0]][trajectoryWumpus[i][1]]==1) triggered_trapsWumpus[trajectoryWumpus[i][0]][trajectoryWumpus[i][1]]=6;
                else triggered_trapsWumpus[trajectoryWumpus[i][0]][trajectoryWumpus[i][1]]=0;
            }

            if(i!=0){
                if(trajectoryWumpus[i][0]<trajectoryWumpus[i-1][0]) weight_point_end-=Field::width()/3;
                else if(trajectoryWumpus[i][0]>trajectoryWumpus[i-1][0])  weight_point_end+=Field::width()/3;
                if(trajectoryWumpus[i][1]<trajectoryWumpus[i-1][1]) height_point_end-=Field::height()/3;
                else if(trajectoryWumpus[i][1]>trajectoryWumpus[i-1][1]) height_point_end+=Field::height()/3;

                if(weight_point_end<0) weight_point_end=0;
                else if(weight_point_end>Field::width()) weight_point_end=Field::width();
                if(height_point_end<0) height_point_end=0;
                else if(height_point_end>Field::height()) height_point_end=Field::height();

                painter.drawLine(QLine(weight_point_begin, height_point_begin, weight_point_end, height_point_end));
                weight_point_begin=weight_point_end;
                height_point_begin=height_point_end;
            }
        }

        for (int i=0; i<triggered_traps.size(); ++i) {
            for (int j=0; j<triggered_traps[0].size(); ++j) {
                triggered_traps[i][j]+=triggered_trapsWumpus[i][j];
            }
        }
    }

    // Траектория призрака
    if(flagTrajectoryGhost){
        QVector<QVector<int>> triggered_trapsGhost(5, QVector<int>(5));
        weight_point_end=Field::width()/3+Field::width()/6+5+rand()%10;
        height_point_end=Field::height()/3+Field::height()/6+5+rand()%10;
        weight_point_begin=weight_point_end;
        height_point_begin=height_point_end;
        painter.setPen(QPen(QColor("orange"), 8, Qt::SolidLine, Qt::FlatCap));
        painter.drawPoint(weight_point_begin, height_point_begin);

        painter.setPen(QPen(QColor("orange"), 5, Qt::SolidLine, Qt::FlatCap));
        for (int i=0; i<trajectoryGhost.size(); ++i) {
            if (!trajectoryGhost.size()-1){
                if(traps[trajectoryGhost[i][0]][trajectoryGhost[i][1]]==2) triggered_trapsGhost[trajectoryGhost[i][0]][trajectoryGhost[i][1]]+=6;
                else if(traps[trajectoryGhost[i][0]][trajectoryGhost[i][1]]==1) triggered_trapsGhost[trajectoryGhost[i][0]][trajectoryGhost[i][1]]+=0;
            }

            if(i!=0){
                if(trajectoryGhost[i][0]<trajectoryGhost[i-1][0]) weight_point_end-=Field::width()/3;
                else if(trajectoryGhost[i][0]>trajectoryGhost[i-1][0]) weight_point_end+=Field::width()/3;
                if(trajectoryGhost[i][1]<trajectoryGhost[i-1][1]) height_point_end-=Field::height()/3;
                else if(trajectoryGhost[i][1]>trajectoryGhost[i-1][1]) height_point_end+=Field::height()/3;

                if(weight_point_end<0) weight_point_end=0;
                else if(weight_point_end>Field::width()) weight_point_end=Field::width();
                if(height_point_end<0) height_point_end=0;
                else if(height_point_end>Field::height()) height_point_end=Field::height();

                painter.drawLine(QLine(weight_point_begin, height_point_begin, weight_point_end, height_point_end));
                weight_point_begin=weight_point_end;
                height_point_begin=height_point_end;
            }
        }

        for (int i=0; i<triggered_traps.size(); ++i) {
            for (int j=0; j<triggered_traps[0].size(); ++j) {
                triggered_traps[i][j]+=triggered_trapsGhost[i][j];
            }
        }
    }

    // Сработанные ловушки
    painter.setPen(QPen(QColor(255, 0, 0, 50), Field::width()/3, Qt::SolidLine, Qt::FlatCap));
    for (int i=1; i<triggered_traps.size()-1; ++i) {
        for (int j=1; j<triggered_traps[0].size()-1; ++j) {
            if(triggered_traps[i][j]>5){
                painter.drawPoint(Field::width()/6+(i-1)*Field::width()/3, Field::height()/6+(j-1)*Field::height()/3);
            }
        }
    }
}

// Генерация ловушек на поле
// Возвращает двумерный вектор, где случайно располагаются:
// 3 веревочки с колокольчиком(=1), 3 детектора протоплазмы(=2), 3 пустые ячейки(=0)
QVector<QVector<int>>& Field::TrapGeneration(QVector<QVector<int>>& traps)
{
    srand(time(NULL));
    int trap[9]={0,0,0,1,1,1,2,2,2};
    std::random_shuffle(trap, trap + 9 );
    int count=0;

    for (int i=1; i<traps.size()-1; ++i) {
        for (int j=1; j<traps[0].size()-1; ++j) {
            traps[i][j]=trap[count];
            count++;
        }
    }
    return traps;
}

// Генерация траектории движения существ.
// Возвращает вектор, в котором записаны позиции(i,j) каждого хода.
// i и j используются как значения позиции элемента в матрице
QVector<QVector<int>>& Field::TrajectoryGeneration(QVector<QVector<int>>& trajectory)
{
    srand(time(NULL));
    trajectory.clear();
    QVector<int> item_trajectory(2);
    item_trajectory[0]=2;
    item_trajectory[1]=2;
    trajectory.push_back(item_trajectory);
    int move=0, prev_i=0, prev_j=0, i=2, j=2;
    bool flagWhile=true;
    int arr_move[4]={-2, -1, 1, 2};
    bool flag_vec=false;

    while (flagWhile) {
        Transition:
            move=arr_move[0+rand()%4];

            if(move==-2) j--;
            else if(move==-1) i--;
            else if(move==2) j++;
            else if(move==1) i++;

            for (int k=0;k<trajectory.size() ;++k ) {
                if(trajectory.value(k).value(0)==i && trajectory.value(k).value(1)==j){
                   flag_vec=true;
                   break;
                }
            }

            if (flag_vec==true) {
                i=prev_i;
                j=prev_j;
                flag_vec=false;

                goto Transition;
            }

            item_trajectory[0]=i;
            item_trajectory[1]=j;
            trajectory.push_back(item_trajectory);
            prev_i=i;
            prev_j=j;

            if(i==0 || i==4 || j==0 || j==4) flagWhile=false;
    }
    return trajectory;
}

// Обновляет траекторию движения для кошки
void Field::UpdateTrajectoryCat()
{
    TrajectoryGeneration(trajectoryCat);
}

// Обновляет траекторию движения для вампуса
void Field::UpdateTrajectoryWumpus()
{
    TrajectoryGeneration(trajectoryWumpus);
}

// Обновляет траекторию движения для призрака
void Field::UpdateTrajectoryGhost()
{
    TrajectoryGeneration(trajectoryGhost);
}

// Обновляет поле с ловушками
void Field::UpdateTrapGeneration()
{
    TrapGeneration(traps);
}
