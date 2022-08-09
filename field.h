#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <algorithm>
#include <QString>
#include <QVector>

//Отрисовывает поле,траектории,ловушки на виджете
class Field : public QWidget
{
    Q_OBJECT

public:
    explicit Field(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *);
    void UpdateTrapGeneration();
    void UpdateTrajectoryCat();
    void UpdateTrajectoryWumpus();
    void UpdateTrajectoryGhost();

private:
    QVector<QVector<int>>& TrapGeneration(QVector<QVector<int>>& traps);
    QVector<QVector<int>>& TrajectoryGeneration(QVector<QVector<int>>& trajectory);
};
#endif // FIELD_H
