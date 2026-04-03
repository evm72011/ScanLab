import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Item {
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
                { value: SL.DeviceType.None, text: "None" },
                { value: SL.DeviceType.OEMPA_1, text: "OEMPA 1" },
                { value: SL.DeviceType.OEMPA_2, text: "OEMPA 2" },
                { value: SL.DeviceType.OEMPA_Max, text: "OEMPA Max" },
                { value: SL.DeviceType.OEMPA_Mini, text: "OEMPA Mini" },
                { value: SL.DeviceType.OEMPA_MC1, text: "OEMPA MC1" },
                { value: SL.DeviceType.OEMPA_MC2, text: "OEMPA MC2" },
                { value: SL.DeviceType.OEMPA_MCmu, text: "OEMPA MCμ" },
                { value: SL.DeviceType.OEMPA_MCmuF, text: "OEMPA MCμF" },
                { value: SL.DeviceType.OEMPA_Micro, text: "OEMPA Micro" }
            ]

            currentValue: backend?.device?.type ?? SL.DeviceType.None

            onActivated: function(value) {
                backend.device.type = value
                backend.device.resetDevice();
                SL.AppSettings.setValue("Hardware/type", value)
            }
        }

        SL.TextField {
            label: qsTr("Address")
            labelWidth: 140
            fieldWidth: 260
            placeholderText: qsTr("Enter device address")
            infoText: qsTr("IP address or device path")

            value:  backend?.device?.address ?? "" // SL.AppSettings.value("Hardware/address", backend?.device?.address ?? "")

            onValueEdited: function(value) {
                backend.device.address = value;
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
            text: backend?.device?.connecting
                  ? qsTr("Connecting...")
                  : backend?.device?.connected
                    ? qsTr("Disconnect")
                    : qsTr("Connect")
            iconSource: backend?.device?.connected
                        ? "qrc:/icons/disconnected.svg"
                        : "qrc:/icons/connected.svg"
            enabled: !backend?.device?.connecting
            busy: !!backend?.device?.connecting

            width: 150

            onClicked: {
                if (backend?.device?.connected) {
                    backend.device.disconnectDevice();
                } else {
                    backend.device.connectDevice()
                }
            }
        }

        Connections {
            target: backend?.device ?? null

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
            detailsText: `Error Code: ${backend?.device?.lastConnectStatusCode ?? ''}`
        }

        SL.MessageDialog {
            id: notImplementedDialog
            messageType: MessageDialog.Type.Info
            shortText: qsTr("Not implemented")
            detailsText: qsTr("The feature is under the construction")
        }

        Item { Layout.fillHeight: true }

        Component.onCompleted: {
            backend.device.address = SL.AppSettings.value(
                "Hardware/address",
                backend.device.address
            )

            backend.device.type = Number(
                SL.AppSettings.value("Hardware/type", backend.device.type)
            )
        }

    }
}
