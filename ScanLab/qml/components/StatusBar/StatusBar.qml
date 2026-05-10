import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

ToolBar {
    id: root
    implicitHeight: SL.Theme.layout.statusBarHeight

    property int connectionState: backend?.connectionFacade?.connectionState ??
                                  SL.ConnectionState.Disconnected

    readonly property bool disconnected: connectionState === SL.ConnectionState.Disconnected
    readonly property bool connecting: connectionState === SL.ConnectionState.Connecting
    readonly property bool connected: connectionState === SL.ConnectionState.Connected
    readonly property bool disconnecting: connectionState === SL.ConnectionState.Disconnecting

    readonly property bool pulsing: backend?.ascanFacade?.running ?? false

    background: Rectangle {
        color: SL.Theme.colors.windowBackground

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
            color: SL.Theme.colors.border
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
            tooltip: qsTr("Connected to device\ns/n: %1").arg(backend?.connectionFacade?.serialNumber)
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

        HumidityStatusChip {
            visible: root.connected
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
        }
    }
}