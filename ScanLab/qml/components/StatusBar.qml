import QtQuick
import QtQuick.Controls

ToolBar {
    id: root
    implicitHeight: 30

    property bool connected: true

    background: Rectangle {
        color: "#161616"
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
            color: "#2a2a2a"
        }
    }

    contentItem: Item {
        anchors.fill: parent

        Row {
            anchors.verticalCenter: parent.verticalCenter
            x: 10
            spacing: 8

            StatusChip {
                iconSource: root.connected ? "qrc:/icons/connected.svg" : "qrc:/icons/disconnected.svg"
                text: root.connected ? "Connected" : "Disconnected"
            }
        }
    }
}
