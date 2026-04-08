import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

ToolBar {
    id: root
    implicitHeight: 30

    property int connectionState: backend?.connection?.connectionState ??
                                  SL.ConnectionState.Disconnected

    readonly property bool disconnected: connectionState === SL.ConnectionState2.Disconnected
    readonly property bool connecting: connectionState === SL.ConnectionState2.Connecting
    readonly property bool connected: connectionState === SL.ConnectionState2.Connected
    readonly property bool disconnecting: connectionState === SL.ConnectionState2.Disconnecting

    readonly property bool pulsing: backend?.device?.pulsing ?? false

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

    contentItem: RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 8

        StatusChip {
            visible: root.disconnected
            iconSource: "qrc:/icons/disconnected.svg"
            text: qsTr("Disconnected")
        }

        StatusChip {
            visible: root.connecting || root.disconnecting
            iconSource: "qrc:/icons/update.svg"
            iconOpacity: 0.8
            rotateIcon: true
            text: root.connecting ? qsTr("Connecting") : qsTr("Disonnecting")
        }

        StatusChip {
            visible: root.connected
            iconSource: "qrc:/icons/connected.svg"
            text: qsTr("Connected")
        }

        StatusChip {
            visible: root.connected
            iconSource: "qrc:/icons/pulsing.svg"
            iconSize: 18
            iconOpacity: root.pulsing ? 1 : 0.7
            pulseBackground: root.pulsing
            text: root.pulsing ? qsTr("Pulsing") : qsTr("Not pulsing")
        }

        Item {
            Layout.fillWidth: true
        }

        TemperatureStatusChip {
            visible: root.connected
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
        }
    }
}