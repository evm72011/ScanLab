import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

RowLayout {
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0
    spacing: 0

    Rectangle {
        Layout.fillHeight: true
        Layout.preferredWidth: 84
        color: SL.Theme.colors.windowBackground

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 8

            SL.IconTabButton {
                Layout.fillWidth: true
                text: qsTr("Device")
                iconSource: "qrc:/icons/device.svg"
                checked: navigation.currentIndex === 0
                onClicked: navigation.currentIndex = 0
            }

            SL.IconTabButton {
               Layout.fillWidth: true
                text: qsTr("A-scan")
                iconSource: "qrc:/icons/ascan.svg"
                iconSize: 30
                checked: navigation.currentIndex === 1
                onClicked: navigation.currentIndex = 1
            }

            SL.IconTabButton {
                Layout.fillWidth: true
                text: qsTr("B-scan")
                iconSource: "qrc:/icons/bscan.svg"
                iconSize: 30
                checked: navigation.currentIndex === 2
                onClicked: navigation.currentIndex = 2
            }

            SL.IconTabButton {
                Layout.fillWidth: true
                text: qsTr("C-scan")
                iconSource: "qrc:/icons/cscan.svg"
                iconSize: 30
                checked: navigation.currentIndex === 3
                onClicked: navigation.currentIndex = 3
            }

            Item {
                Layout.fillHeight: true
            }

            /*
            SL.IconTabButton {
                Layout.fillWidth: true
                text: qsTr("Settings")
                iconSource: "qrc:/icons/cog.svg"
                onClicked: {
                    // например:
                    console.log("Settings clicked")
                }
            }
            */
        }

        Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 1
            color: SL.Theme.colors.border
        }
    }

    ColumnLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 0

        StackLayout {
            id: navigation
            Layout.fillWidth: true
            Layout.fillHeight: true

            SL.HardwarePage {}

            SL.AScanPage {
                active: navigation.currentIndex === 1
            }

            SL.ScanBPage {
                active: navigation.currentIndex === 2
            }

            SL.ScanCPage {
                active: navigation.currentIndex === 3
            }
        }

        SL.StatusBar {
            id: statusBar
            Layout.fillWidth: true
            Layout.preferredHeight: 32
        }
    }
}
