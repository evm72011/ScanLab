import QtQuick
import QtQuick.Controls
import ScanLab 1.0 as SL

ToolBar {
    id: root
    implicitHeight: 30

    property bool connected: true
    property bool pulsing: false

    background: Rectangle {
        color: SL.Theme.colors.statusbarBackground
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
            color: SL.Theme.colors.statusbarBackground
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

            StatusChip {
                iconSource: root.pulsing ? "qrc:/icons/connected.svg" : "qrc:/icons/disconnected.svg"
                text: root.pulsing ? "Pulsing" : "Not pulsing"
                visible: root.connected
            }
        }
    }
}
