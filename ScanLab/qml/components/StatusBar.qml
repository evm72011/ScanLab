import QtQuick
import QtQuick.Controls
import ScanLab as SL

ToolBar {
    id: root
    implicitHeight: 30

    property bool connected: backend?.device?.connected ?? false
    property bool connecting: backend?.device?.connecting ?? false
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
                visible: root.connecting
                iconSource: "qrc:/icons/update.svg"
                iconOpacity: 0.8
                rotateIcon: true
                text: qsTr("Connecting")
            }

            StatusChip {
                visible: !root.connecting && root.connected
                iconSource: "qrc:/icons/connected.svg"
                text: qsTr("Connected")
            }

            StatusChip {
                visible: !root.connecting && !root.connected
                iconSource: "qrc:/icons/disconnected.svg"
                text: qsTr("Disconnected")
            }

            StatusChip {
                iconSource: root.pulsing
                    ? "qrc:/icons/connected.svg"
                    : "qrc:/icons/disconnected.svg"

                text: root.pulsing
                    ? qsTr("Pulsing")
                    : qsTr("Not pulsing")

                visible: root.connected && !root.connecting
            }
        }
    }
}
