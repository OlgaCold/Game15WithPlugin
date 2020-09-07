import QtQuick 2.9

Rectangle {

    id: root
    property alias text: label.text
    property bool isVoid: false

    color: isVoid ? "transparent" : "#cd853f"
    border.color: isVoid ? "transparent" : "#8b4513"
    radius: 5

    Text {
        id: label
        anchors.centerIn: parent
        color: isVoid ? "transparent" : "black"
        font.pixelSize: 35
    }
}
