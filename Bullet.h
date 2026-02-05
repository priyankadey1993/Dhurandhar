#ifndef BULLET_H
#define BULLET_H

#include<QPointF>
#include<QString>

struct Bullet{
    QPointF pos;
    QPointF velocity;
    Bullet(QPointF p, QPointF v) : pos(p), velocity(v) {}
};


#endif // BULLET_H
