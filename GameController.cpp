#include "GameController.h"
#include <Qt>
#include <QDebug>
#include<QLineF>

GameController::GameController(QObject *parent) :QObject(parent)
{
    startGame();
    connect(&m_timer,&QTimer::timeout,this,&GameController::gameLoop);
    m_timer.start(33);
}

void GameController::startGame()
{
    qDebug()<<"start game";
    // Clear existing enemies
    m_enemies.clear();
    m_bullets.clear();

    m_player.pos = QPointF(400, 300);
    m_player.direction = "down";

    m_enemies.append({QPointF(100, 100), "down"});
    m_enemies.append({QPointF(300, 100), "up"});
    m_enemies.append({QPointF(500, 100), "left"});
    m_enemies.append({QPointF(700, 100), "right"});
    m_enemies.append({QPointF(200, 300), "down"});
    m_enemies.append({QPointF(600, 300), "up"});

    // Reset score
    m_score = 0;
    emit scoreChanged();

    // Reset game states
    m_gameOver = false;
    m_levelComplete = false;
    emit gameOverChanged();
    emit levelCompleteChanged();

    // Start game loop
    m_gameRunning = true;
    emit playerChanged();
    emit enemiesChanged();
}

void GameController::restartGame()
{
    startGame();
}

void GameController:: handleKey(int key)
{
    // Don't process keys if game is over or level complete
    if (m_gameOver || m_levelComplete) {
        return;
    }

    m_pressedKeys.insert(key);
    if(key == Qt::Key_Space){
        QPointF velocity;
        if(m_player.direction == "up") velocity = QPointF(0, -15);
        else if(m_player.direction == "down") velocity = QPointF(0, 15);
        else if(m_player.direction == "left") velocity = QPointF(-15, 0);
        else if(m_player.direction == "right") velocity = QPointF(15, 0);
        else velocity = QPointF(0, -15);

        m_bullets.append(Bullet(m_player.pos + QPointF(32, 32), velocity));
        emit bulletsChanged();
    }
}

void GameController::handleKeyReleased(int key)
{
    m_pressedKeys.remove(key);
}

void GameController::gameLoop()
{
    // Don't update game if it's over or level is complete
    if (m_gameOver || m_levelComplete) {
        return;
    }

    const qreal speed = 5;
    // Continuous movement for held keys
    for (int key : m_pressedKeys) {
        if (key == Qt::Key_W) {
            m_player.pos.ry() -= speed;
            m_player.direction = "up";
        }
        if (key == Qt::Key_S) {
            m_player.pos.ry() += speed;
            m_player.direction = "down";
        }
        if (key == Qt::Key_A) {
            m_player.pos.rx() -= speed;
            m_player.direction = "left";
        }
        if (key == Qt::Key_D) {
            m_player.pos.rx() += speed;
            m_player.direction = "right";
        }
    }

    // Clamp player
    m_player.pos.setX(qBound(0.0, m_player.pos.x(), 760.0));
    m_player.pos.setY(qBound(0.0, m_player.pos.y(), 560.0));

    // Move bullets
    for (int i = m_bullets.size() - 1; i >= 0; --i) {
        m_bullets[i].pos += m_bullets[i].velocity;
        if (m_bullets[i].pos.x() < 0 || m_bullets[i].pos.x() > 800 ||
            m_bullets[i].pos.y() < 0 || m_bullets[i].pos.y() > 600) {
            m_bullets.removeAt(i);
        }
    }

    // Enemies follow player
    for (int i = 0; i < m_enemies.size(); ++i) {
        QPointF d = m_player.pos - m_enemies[i].pos;
        qreal len = qSqrt(QPointF::dotProduct(d, d));
        if (len > 0) {
            d /= len;
            m_enemies[i].pos += d * 2;
            m_enemies[i].direc = qAbs(d.x()) > qAbs(d.y())
                                     ? (d.x() > 0 ? "right" : "left")
                                     : (d.y() > 0 ? "down" : "up");
        }
    }

    // Collision detection: bullets hitting enemies
    for (int i = m_bullets.size() - 1; i >= 0; --i) {
        for (int j = m_enemies.size() - 1; j >= 0; --j) {
            // Check if bullet hits enemy (simple distance check)
            QPointF bulletCenter = m_bullets[i].pos + QPointF(8, 8);  // Bullet center (assuming 16x16 bullet)
            QPointF enemyCenter = m_enemies[j].pos + QPointF(32, 32);  // Enemy center (assuming 64x64 enemy)
            QPointF diff = bulletCenter - enemyCenter;
            qreal distance = qSqrt(QPointF::dotProduct(diff, diff));

            // If distance is less than combined radius (bullet + enemy)
            if (distance < 40) { // Collision threshold
                // Remove both bullet and enemy
                m_enemies.removeAt(j);
                m_bullets.removeAt(i);

                // Increase score
                m_score += 100;
                emit scoreChanged();

                break; // Bullet can only hit one enemy
            }
        }
    }

    // Check if player collides with any enemy (GAME OVER)
    QPointF playerCenter = m_player.pos + QPointF(32, 32); // Player center (64x64)
    for (int i = 0; i < m_enemies.size(); ++i) {
        QPointF enemyCenter = m_enemies[i].pos + QPointF(32, 32);
        QPointF diff = playerCenter - enemyCenter;
        qreal distance = qSqrt(QPointF::dotProduct(diff, diff));

        // If enemy touches player (collision distance < 50 pixels)
        if (distance < 50) {
            m_gameOver = true;
            m_gameRunning = false;
            emit gameOverChanged();
            qDebug() << "Game Over! Player was caught by enemy!";
            return; // Stop game loop
        }
    }

    // Check if all enemies are defeated (LEVEL COMPLETE)
    if (m_enemies.isEmpty()) {
        m_levelComplete = true;
        m_gameRunning = false;
        emit levelCompleteChanged();
        qDebug() << "Level Complete! Waiting for Dhurandhar Part 2...";
        return; // Stop game loop
    }

    emit playerChanged();
    emit enemiesChanged();
    emit bulletsChanged();
}
