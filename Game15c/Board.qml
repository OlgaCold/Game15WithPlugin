import QtQuick 2.9

Rectangle{

    id: root

    property alias model: grid.model
    property alias delegate: grid.delegate
    property int gridCellSize
    property int margin

    color: "#faebd7"
    border.color: "#8b4513"

    GridView {

        id: grid

        anchors.fill: parent

        interactive: false
        cellWidth: parent.width/parent.gridCellSize
        cellHeight: cellWidth

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }
        move: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }
    }
}
