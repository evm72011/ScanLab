import QtQuick
import QtQuick.Controls
import ScanLab as SL

ToolBar {
    id: root
    implicitHeight: 30

    property int connectionState: backend?.device?.connectionState ??
                                  SL.ConnectionState.Disconnected

    readonly property bool disconnected: connectionState === SL.ConnectionState.Disconnected
    readonly property bool connecting: connectionState === SL.ConnectionState.Connecting
    readonly property bool connected: connectionState === SL.ConnectionState.Connected

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
                visible: root.disconnected
                iconSource: "qrc:/icons/disconnected.svg"
                text: qsTr("Disconnected")
            }

            StatusChip {
                visible: root.connecting
                iconSource: "qrc:/icons/update.svg"
                iconOpacity: 0.8
                rotateIcon: true
                text: qsTr("Connecting")
            }

            StatusChip {
                visible: root.connected
                iconSource: "qrc:/icons/connected.svg"
                text: qsTr("Connected")
            }

            StatusChip {
                visible: root.connected && !root.pulsing
                iconSource: "qrc:/icons/disconnected.svg"
                text: qsTr("Not pulsing")
            }

            StatusChip {
                visible: root.pulsing
                iconSource: "qrc:/icons/connected.svg"
                text: qsTr("Pulsing")
            }
        }
    }
}
