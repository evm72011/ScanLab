import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
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

            SL.TextField {
                label: qsTr("Load config file")
                labelWidth: 140
                fieldWidth: 260

                value: configFileFacade?.loadPath ?? ""
                toolTipText: value
                enabled: root.connected && !configFileFacade?.busy

                onValueEdited: function(value) {
                    configFileFacade.loadPath = value
                }

                onEditingFinished: function(value) {
                    SL.AppSettings.setValue("Hardware/configFile", value)
                }
            }

            SL.Button {
                text: qsTr("...")
                width: 40
                enabled: root.connected && !configFileFacade?.busy

                onClicked: {
                    loadConfigFileDialog.open()
                }
            }

            SL.Button {
                text: qsTr("Load")
                width: 140
                enabled: root.connected
                         && !configFileFacade?.busy
                         && (configFileFacade?.loadPath ?? "") !== ""

                busy: configFileFacade?.busy ?? false

                onClicked: {
                    configFileFacade.loadConfigFile()
                }
            }
        }

        RowLayout {
            spacing: 8

            SL.TextField {
                label: qsTr("Save config file")
                labelWidth: 140
                fieldWidth: 260

                value: configFileFacade?.savePath ?? ""
                toolTipText: value

                enabled: root.connected && !configFileFacade?.busy

                onValueEdited: function(value) {
                    configFileFacade.savePath = value
                }

                onEditingFinished: function(value) {
                    SL.AppSettings.setValue("Hardware/saveConfigFile", value)
                }
            }

            SL.Button {
                text: qsTr("...")
                width: 40

                enabled: root.connected && !configFileFacade?.busy

                onClicked: {
                    saveConfigFileDialog.open()
                }
            }

            SL.Button {
                text: qsTr("Save")
                width: 140

                enabled: root.connected
                         && !configFileFacade?.busy
                         && (configFileFacade?.savePath ?? "") !== ""

                busy: configFileFacade?.busy ?? false

                onClicked: {
                    configFileFacade.saveConfigFile()
                }
            }
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

            configFileFacade.loadPath = SL.AppSettings.value("Hardware/configFile", "")
        }
    }

    FileDialog {
        id: loadConfigFileDialog

        title: qsTr("Open config file")
        nameFilters: [
            qsTr("OEMPA config files (*.txt *.bin)"),
            qsTr("All files (*)")
        ]

        onAccepted: {
            const path = selectedFile.toString().replace("file:///", "")
            console.log(path);

            configFileFacade.loadPath = path
            SL.AppSettings.setValue("Hardware/configFile", path)
        }
    }

    FileDialog {
        id: saveConfigFileDialog

        title: qsTr("Save config file")

        fileMode: FileDialog.SaveFile

        nameFilters: [
            qsTr("OEMPA config files (*.txt *.bin)"),
            qsTr("All files (*)")
        ]

        onAccepted: {
            const path = selectedFile.toString().replace("file:///", "")

            configFileFacade.savePath = path

            SL.AppSettings.setValue("Hardware/saveConfigFile", path)
        }
    }
}
