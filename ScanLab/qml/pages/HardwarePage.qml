import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

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
                { value: SL.DeviceType.OEMPAMax, text: "OEMPA Max" },
                { value: SL.DeviceType.OEMPAMini, text: "OEMPA Mini" }
            ]

            currentValue: backend?.device?.type ?? SL.DeviceType.None

            onActivated: function(value) {
                backend.device.type = value
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
            width: 160

            onClicked: {
                notImplementedDialog.open();
            }
        }

        SL.Button {
            text: backend?.device?.connecting ? qsTr("Connecting...") : qsTr("Connect")
            iconSource: "qrc:/icons/connected.svg"
            enabled: !backend?.device?.connecting

            width: 160

            onClicked: {
                backend.device.connectDevice()
            }
        }

        Connections {
            target: backend?.device

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
