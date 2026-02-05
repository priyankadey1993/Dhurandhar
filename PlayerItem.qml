import QtQuick

Item {
    id:playerItem
    width:64
    height:64

    property string direction : "up"

    Image{
        id:playerImage
        anchors.fill: parent
        source: {
            if(direction === "up") return "qrc:/images/up.png";
            else if(direction === "down") return "qrc:/images/down.png";
            else if(direction === "left") return "qrc:/images/left.png";
            else if(direction === "right") return "qrc:/images/right.png";
            else return "qrc:/images/down.png";
        }
    }

}
