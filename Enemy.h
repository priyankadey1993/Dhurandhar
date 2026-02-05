#ifndef ENEMY_H
#define ENEMY_H

#include<QPointF>
#include<QString>

struct Enemy{
    QPointF pos;
    QString direc;

    Enemy(QPointF p,QString dir = "down") :pos(p),direc(dir){}

};

#endif // ENEMY_H
