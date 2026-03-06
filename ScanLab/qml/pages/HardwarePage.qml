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

            currentValue: backend.device.type

            onActivated: function(value) {
                console.log("Selected enum:", value)
                console.log("Selected text:", currentText)
                backend.device.type = value
            }
        }

        SL.TextField {
            label: qsTr("Address")
            labelWidth: 140
            fieldWidth: 260
            placeholderText: qsTr("Enter device address")
            infoText: qsTr("IP address or device path")
            onAccepted: console.log("Enter pressed:", text)
        }

        SL.Button {
            text: qsTr("Ping")
            onClicked: device.connect()
        }

        SL.Button {
            text: qsTr("Connect")
            iconSource: "qrc:/icons/connected.svg"
            onClicked: function(value) {
                console.log("Backend device type:", backend.device.type)
            }
        }


        Item { Layout.fillHeight: true }

    }
}
