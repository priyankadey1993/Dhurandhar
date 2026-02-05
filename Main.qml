import QtQuick
import QtQuick.Window
import QtMultimedia

Window {
    width: 800
    height: 600
    visible: true
    title: "Dhurandhar"

    property bool gameStarted: false

    Rectangle {
        anchors.fill: parent
        color: "black"

        // INTRO SCREEN

        Item {
            anchors.fill: parent
            visible: !gameStarted

            Image {
                id: logo
                source: "qrc:/images/dhurandhar-movie-logo-png.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                opacity: 0

                SequentialAnimation on opacity {
                    NumberAnimation { to: 1; duration: 1500 }
                    PauseAnimation { duration: 3000 }
                    NumberAnimation { to: 0; duration: 1000 }
                }
            }

            Image {
                id: ranveer
                source: "qrc:/images/ranveersingh_intro_img.jpg"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                opacity: 0

                SequentialAnimation on opacity {
                    PauseAnimation { duration: 5500 }
                    NumberAnimation { to: 1; duration: 1500 }
                    PauseAnimation { duration: 3000 }
                    NumberAnimation { to: 0; duration: 1000
                    }
                }
            }
        }

        // GAME SCREEN
        GameView {
            id: gameView
            anchors.fill: parent
            visible: gameStarted
            focus: true
            onVisibleChanged: {
                            if (visible) {
                                forceActiveFocus()
                                gameController.startGame()
                            }
                        }
        }
    }

    Timer {
            id: introTimer
            interval: 11000
            running: true
            repeat: false
            onTriggered: {
                gameStarted = true
                gameController.startGame()
            }
        }

    MediaPlayer {
        id: musicPlayer
        source: "qrc:/audio/dhurandhar_title.mp3"
        audioOutput: AudioOutput { volume: 1.0 }
    }

    Component.onCompleted: musicPlayer.play()
}
/*
Item {
    id: gameView
    anchors.fill: parent
    focus: true

    property int score: 0

    Image {
        anchors.fill: parent
        source: "qrc:/images/background.jpg"
        fillMode: Image.Stretch
    }

    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Score: " + score
        font.pixelSize: 20
        color: "white"
    }

    PlayerItem {
        x: gameController.playerX
        y: gameController.playerY
        direction: gameController.playerDirection
    }

    Repeater {
        model: gameController.enemyCount
        EnemyItem {
            x: gameController.enemyX(index)
            y: gameController.enemyY(index)
            direction: gameController.enemyDirection(index)
        }
    }

    Repeater {
        model: gameController.bulletCount
        BulletItem {
            x: gameController.bulletX(index)
            y: gameController.bulletY(index)
        }
    }

    Keys.onPressed: {
        gameController.handleKey(event.key)
        event.accepted = true
    }

    Keys.onReleased: {
        gameController.handleKeyReleased(event.key)
        event.accepted = true
    }

    Connections {
        target: gameController
        function onScoreChanged() {
            score += 100
        }
    }
}

*/
