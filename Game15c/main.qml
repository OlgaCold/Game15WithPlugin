import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

import GameModel 1.0

ApplicationWindow {

    id: root

    title: qsTr("Game of 15")
    visible: true
    width: 530
    height: 600
    color:"#deb887"

    minimumWidth: 530
    minimumHeight: 600

    Board {

        id: board

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -40

        margin: 30
        width: Math.min(parent.height - margin - button.height, parent.width - margin)
        height: width
        gridCellSize: items.gridSize


        model: GameModel { id: items }
        delegate: BlockDelegate {

            id: blockDelegate
            width: parent.width/items.gridSize
            height: width
            text: model.display
            isVoid: model.isvoid

            onClicked: {
                if(items.move(oldP)){
                    messageDialog.open()
                }
            }
        }
    }

    MixButton {
        id: button

        anchors.margins: 10
        anchors.bottom: parent.bottom

        text: "<b>Mix</b>";
        textColor: "#8b4513"
        onClicked: items.mix()

    }

    MessageDialog {

        id: messageDialog
        text: "You WIN!!!"

        onAccepted: {
            messageDialog.close()
        }
    }

}
