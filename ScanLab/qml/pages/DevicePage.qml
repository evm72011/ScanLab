import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Item {
    id: root

    readonly property var connectionFacade: backend?.connectionFacade ?? null
    readonly property var configFileFacade: backend?.configFileFacade ?? null

    property int connectionState: connectionFacade?.connectionState ?? SL.ConnectionState.Disconnected

    readonly property bool disconnected: connectionState === SL.ConnectionState.Disconnected
    readonly property bool connecting: connectionState === SL.ConnectionState.Connecting
    readonly property bool connected: connectionState === SL.ConnectionState.Connected
    readonly property bool disconnecting: connectionState === SL.ConnectionState.Disconnecting

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
                { value: SL.DeviceTypeQml.None, text: "None" },
                { value: SL.DeviceTypeQml.OEMPA_1, text: "OEMPA 1" },
                { value: SL.DeviceTypeQml.OEMPA_2, text: "OEMPA 2" },
                { value: SL.DeviceTypeQml.OEMPA_Max, text: "OEMPA Max" },
                { value: SL.DeviceTypeQml.OEMPA_Mini, text: "OEMPA Mini" },
                { value: SL.DeviceTypeQml.OEMPA_MC1, text: "OEMPA MC1" },
                { value: SL.DeviceTypeQml.OEMPA_MC2, text: "OEMPA MC2" },
                { value: SL.DeviceTypeQml.OEMPA_MCmu, text: "OEMPA MCμ" },
                { value: SL.DeviceTypeQml.OEMPA_MCmuF, text: "OEMPA MCμF" },
                { value: SL.DeviceTypeQml.OEMPA_Micro, text: "OEMPA Micro" }
            ]

            currentValue: connectionFacade?.deviceType ?? SL.DeviceTypeQml.None
            enabled: root.disconnected

            onActivated: function(value) {
                connectionFacade.deviceType = value
                SL.AppSettings.setValue("Hardware/type", value)
            }
        }

        SL.TextField {
            label: qsTr("Address")
            labelWidth: 140
            fieldWidth: 260
            placeholderText: qsTr("Enter device address")
            infoText: qsTr("IP address or device path")

            value:  connectionFacade?.address ?? ""
            enabled: root.disconnected

            onValueEdited: function(value) {
                connectionFacade.address = value;
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
                      : root.disconnecting
                        ? qsTr("Disconnecting")
                        : qsTr("Connect")
            iconSource: root.connected
                        ? "qrc:/icons/disconnected.svg"
                        : "qrc:/icons/connected.svg"
            enabled: root.connected || root.disconnected
            busy: root.connecting || root.disconnecting

            width: 150

            onClicked: {
                if (root.connected) {
                    connectionFacade.disconnectDevice();
                } else {
                    connectionFacade.connectDevice()
                }
            }
        }

        RowLayout {
            spacing: 8

            SL.DropDown {
                label: qsTr("Config file")
                enabled: connected
                labelWidth: 140
                fieldWidth: 260
                currentValue: configFileFacade?.selectedConfigFile

                model: configFileFacade?.availableConfigFiles.map(function(fileName) {
                    return {
                        text: fileName,
                        value: fileName
                    }
                }) ?? []


                onActivated: function(fileName) {
                    backend.configFileFacade.selectedConfigFile = fileName
                    SL.AppSettings.setValue("Hardware/configFile", fileName)
                }
            }

            SL.Button {
                text: qsTr("Load to device")
                width: 140
                enabled: connected

                onClicked: {
                    backend.configFileFacade.loadSelectedConfigFile()
                }
            }
        }

        Connections {
            target: connectionFacade ?? null

            function onConnectionFailure() {
                connectionErrorDialog.open()
            }
        }

        SL.MessageDialog {
            id: connectionErrorDialog
            messageType: MessageDialog.Type.Error
            dialogTitle: qsTr("Unable to connect")
            shortText: connectionFacade?.errorText ?? ""
            //detailsText: qsTr("Check the address and make sure the device is powered on.")
            errorCode: connectionFacade?.errorCode ?? ""
        }

        SL.MessageDialog {
            id: notImplementedDialog
            messageType: MessageDialog.Type.Info
            dialogTitle: qsTr("Not implemented")
            shortText: qsTr("The feature is under the construction")
        }

        Item { Layout.fillHeight: true }

        Component.onCompleted: {
            connectionFacade.address = SL.AppSettings.value(
                "Hardware/address",
                backend.connectionFacade.address
            )

            connectionFacade.deviceType = Number(
                SL.AppSettings.value("Hardware/type", backend.connectionFacade.deviceType)
            )

            backend.configFileFacade.refreshConfigFiles()
            backend.configFileFacade.selectedConfigFile = SL.AppSettings.value("Hardware/configFile", "")
        }
    }
}
