import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Item {
    id: root

    property int connectionState: backend?.connection?.connectionState ??
                                  SL.ConnectionState2.Disconnected

    readonly property bool disconnected: connectionState === SL.ConnectionState2.Disconnected
    readonly property bool connecting: connectionState === SL.ConnectionState2.Connecting
    readonly property bool connected: connectionState === SL.ConnectionState2.Connected

    Rectangle {
        anchors.fill: parent
        color: SL.Theme.colors.windowBackground
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        SL.DropDown {
            label: qsTr("Device")
            labelWidth: 140
            fieldWidth: 260
            infoText: qsTr("Select the connected device")

            model: [
                { value: SL.DeviceType2Qml.None, text: "None" },
                { value: SL.DeviceType2Qml.OEMPA_1, text: "OEMPA 1" },
                { value: SL.DeviceType2Qml.OEMPA_2, text: "OEMPA 2" },
                { value: SL.DeviceType2Qml.OEMPA_Max, text: "OEMPA Max" },
                { value: SL.DeviceType2Qml.OEMPA_Mini, text: "OEMPA Mini" },
                { value: SL.DeviceType2Qml.OEMPA_MC1, text: "OEMPA MC1" },
                { value: SL.DeviceType2Qml.OEMPA_MC2, text: "OEMPA MC2" },
                { value: SL.DeviceType2Qml.OEMPA_MCmu, text: "OEMPA MCμ" },
                { value: SL.DeviceType2Qml.OEMPA_MCmuF, text: "OEMPA MCμF" },
                { value: SL.DeviceType2Qml.OEMPA_Micro, text: "OEMPA Micro" }
            ]

            currentValue: backend?.connection?.deviceType ?? SL.DeviceType2Qml.None
            enabled: root.disconnected

            onActivated: function(value) {
                backend.connection.deviceType = value
                backend.connection.resetDevice();
                SL.AppSettings.setValue("Hardware/type", value)
            }
        }

        SL.TextField {
            label: qsTr("Address")
            labelWidth: 140
            fieldWidth: 260
            placeholderText: qsTr("Enter device address")
            infoText: qsTr("IP address or device path")

            value:  backend?.connection?.address ?? ""
            enabled: root.disconnected

            onValueEdited: function(value) {
                backend.connection.address = value;
            }

            onEditingFinished: function(value) {
                SL.AppSettings.setValue("Hardware/address", value)
            }
        }

        SL.Button {
            text: qsTr("Ping")
            width: 150

            onClicked: {
                notImplementedDialog.open();
            }
        }

        SL.Button {
            text: root.connecting
                    ? qsTr("Connecting...")
                    : root.connected
                      ? qsTr("Disconnect")
                      : qsTr("Connect")
            iconSource: root.connected
                        ? "qrc:/icons/disconnected.svg"
                        : "qrc:/icons/connected.svg"
            enabled: !root.connecting
            busy: root.connecting

            width: 150

            onClicked: {
                if (root.connected) {
                    backend.connection.disconnectDevice();
                } else {
                    backend.connection.connectDevice()
                }
            }
        }

        Connections {
            target: backend?.connection ?? null

            function onConnectFinished(result) {
                if (result !== 0) {
                    connectionErrorDialog.open()
                }
            }
        }

        SL.MessageDialog {
            id: connectionErrorDialog
            messageType: MessageDialog.Type.Error
            shortText: qsTr("Connection error")
            detailsText: `Error Code: ${backend?.connection?.lastConnectStatusCode ?? ''}`
        }

        SL.MessageDialog {
            id: notImplementedDialog
            messageType: MessageDialog.Type.Info
            shortText: qsTr("Not implemented")
            detailsText: qsTr("The feature is under the construction")
        }

        Item { Layout.fillHeight: true }

        Component.onCompleted: {
            backend.connection.address = SL.AppSettings.value(
                "Hardware/address",
                backend.device.address
            )

            backend.connection.deviceType = Number(
                SL.AppSettings.value("Hardware/type", backend.connection.deviceType)
            )
        }
    }
}
