#ifndef PLAYER_H
#define PLAYER_H

#include <QPointF>
#include <QString>

struct Player {
    QPointF pos{400, 300}; // center bottom
    QString direction = "up";
};

#endif // PLAYER_H
