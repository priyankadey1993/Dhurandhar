import QtQuick

Item {
    id: enemyItem
    width: 64
    height: 64

    property string direction: "down"

    Image {
        id: enemyImage
        anchors.fill: parent
        source: {
            if(direction === "up") return "qrc:/images/TUp.jpg";
            else if(direction === "down") return "qrc:/images/TDown.jpg";
            else if(direction === "left") return "qrc:/images/TLeft.jpg";
            else if(direction === "right") return "qrc:/images/TRight.png";
            else return "qrc:/images/TUp.jpg";
        }
    }
}
