#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QPointF>
#include <QTimer>
#include <QString>
#include <Player.h>
#include <Enemy.h>
#include<QSet>
#include <Bullet.h>

struct Screen{
    float screenHeight = 600.00;
    float screenWidth = 800.00;
    float personHeight = 64.00 ;
    float personWidth = 64.00;
};

class GameController :public QObject
{
    Q_OBJECT
    Q_PROPERTY(int enemyCount READ enemyCount NOTIFY enemiesChanged);
    Q_PROPERTY(int bulletCount READ bulletCount NOTIFY bulletsChanged);
    Q_PROPERTY(QString playerDirection READ playerDirection NOTIFY playerChanged);
    Q_PROPERTY(qreal playerX READ playerX NOTIFY playerChanged)
    Q_PROPERTY(qreal playerY READ playerY NOTIFY playerChanged)
    Q_PROPERTY(int score READ score NOTIFY scoreChanged)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)
    Q_PROPERTY(bool levelComplete READ levelComplete NOTIFY levelCompleteChanged)

public:
    explicit GameController(QObject *parent = nullptr);
    int enemyCount() const {return m_enemies.size();}
    int bulletCount() const { return m_bullets.size(); }
    QString playerDirection() const { return m_player.direction; }
    int score() const { return m_score; }
    bool gameOver() const { return m_gameOver; }
    bool levelComplete() const { return m_levelComplete; }

    Q_INVOKABLE qreal enemyX(int index) const {return m_enemies[index].pos.x();}
    Q_INVOKABLE qreal enemyY(int index) const {return m_enemies[index].pos.y();}
    Q_INVOKABLE QString enemyDirection(int index) const {return m_enemies[index].direc;};

    Q_INVOKABLE qreal bulletX(int index) const {return m_bullets[index].pos.x();}
    Q_INVOKABLE qreal bulletY(int index) const {return m_bullets[index].pos.y();}

    Q_INVOKABLE void handleKey(int key);
    Q_INVOKABLE void handleKeyReleased(int key);

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void restartGame();

    Q_INVOKABLE qreal playerX() const { return m_player.pos.x(); }
    Q_INVOKABLE qreal playerY() const { return m_player.pos.y(); }

signals:
    void enemiesChanged();
    void bulletsChanged();
    void playerChanged();
    void scoreChanged();
    void gameOverChanged();
    void levelCompleteChanged();

private slots:
    void gameLoop();

private:
    Player m_player;
    QVector<Enemy> m_enemies;
    QVector<Bullet> m_bullets;
    QTimer m_timer;
    int m_score = 0;
    QSet<int> m_pressedKeys;
    Screen screen;
    bool m_gameRunning = false;
    bool m_gameOver = false;
    bool m_levelComplete = false;
};

#endif
