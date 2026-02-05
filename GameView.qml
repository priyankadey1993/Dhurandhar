import QtQuick

Item {
    id: gameView
    anchors.fill: parent
    focus: true

    Image {
        anchors.fill: parent
        source: "qrc:/images/background.jpg"
        fillMode: Image.Stretch
    }

    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        text: "Score: " + gameController.score
        font.pixelSize: 24
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "black"
    }

    // Player
    PlayerItem {
        x: gameController.playerX
        y: gameController.playerY
        direction: gameController.playerDirection
        visible: !gameController.gameOver && !gameController.levelComplete
    }

    // Enemies - recreate when enemiesChanged signal fires
    Repeater {
        model: gameController.enemyCount
        delegate: EnemyItem {
            required property int index
            visible: !gameController.gameOver && !gameController.levelComplete

            Component.onCompleted: {
                updatePosition()
            }

            function updatePosition() {
                x = gameController.enemyX(index)
                y = gameController.enemyY(index)
                direction = gameController.enemyDirection(index)
            }

            Connections {
                target: gameController
                function onEnemiesChanged() {
                    updatePosition()
                }
            }
        }
    }

    // Bullets - recreate when bulletsChanged signal fires
    Repeater {
        model: gameController.bulletCount
        delegate: BulletItem {
            required property int index
            visible: !gameController.gameOver && !gameController.levelComplete

            Component.onCompleted: {
                updatePosition()
            }

            function updatePosition() {
                x = gameController.bulletX(index)
                y = gameController.bulletY(index)
            }

            Connections {
                target: gameController
                function onBulletsChanged() {
                    updatePosition()
                }
            }
        }
    }

    // Game Over Screen
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.85
        visible: gameController.gameOver

        Column {
            anchors.centerIn: parent
            spacing: 30

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "GAME OVER"
                font.pixelSize: 72
                font.bold: true
                color: "red"
                style: Text.Outline
                styleColor: "darkred"
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "You Were Caught!"
                font.pixelSize: 32
                color: "white"
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Final Score: " + gameController.score
                font.pixelSize: 36
                font.bold: true
                color: "yellow"
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 250
                height: 60
                color: "darkred"
                radius: 10
                border.color: "red"
                border.width: 3

                Text {
                    anchors.centerIn: parent
                    text: "RESTART (R)"
                    font.pixelSize: 24
                    font.bold: true
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: gameController.restartGame()
                    hoverEnabled: true
                    onEntered: parent.color = "red"
                    onExited: parent.color = "darkred"
                }
            }
        }
    }

    // Level Complete Screen
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.9
        visible: gameController.levelComplete

        Column {
            anchors.centerIn: parent
            spacing: 30

            // Dhurandhar logo or title
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "🎉 LEVEL COMPLETE! 🎉"
                font.pixelSize: 56
                font.bold: true
                color: "gold"
                style: Text.Outline
                styleColor: "darkorange"
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "All Enemies Defeated!"
                font.pixelSize: 32
                color: "white"
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Final Score: " + gameController.score
                font.pixelSize: 40
                font.bold: true
                color: "yellow"
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 500
                height: 100
                color: "darkblue"
                radius: 15
                border.color: "cyan"
                border.width: 4

                Column {
                    anchors.centerIn: parent
                    spacing: 10

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "WAIT FOR"
                        font.pixelSize: 28
                        color: "white"
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "DHURANDHAR PART 2"
                        font.pixelSize: 36
                        font.bold: true
                        color: "cyan"
                        style: Text.Outline
                        styleColor: "blue"
                    }
                }
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Coming Soon..."
                font.pixelSize: 24
                font.italic: true
                color: "lightgray"

                SequentialAnimation on opacity {
                    loops: Animation.Infinite
                    NumberAnimation { to: 0.3; duration: 1000 }
                    NumberAnimation { to: 1.0; duration: 1000 }
                }
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 250
                height: 50
                color: "darkgreen"
                radius: 10
                border.color: "green"
                border.width: 2

                Text {
                    anchors.centerIn: parent
                    text: "PLAY AGAIN (R)"
                    font.pixelSize: 20
                    font.bold: true
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: gameController.restartGame()
                    hoverEnabled: true
                    onEntered: parent.color = "green"
                    onExited: parent.color = "darkgreen"
                }
            }
        }
    }

    Keys.onPressed: {
        // R key to restart
        if (event.key === Qt.Key_R && (gameController.gameOver || gameController.levelComplete)) {
            gameController.restartGame()
            event.accepted = true
            return
        }

        // Normal game controls
        gameController.handleKey(event.key)
        event.accepted = true
    }

    Keys.onReleased: {
        gameController.handleKeyReleased(event.key)
        event.accepted = true
    }
}
