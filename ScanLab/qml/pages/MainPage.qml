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

        Column {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 8
            spacing: 8

            SL.IconTabButton {
                width: parent.width
                text: qsTr("Device")
                iconSource: "qrc:/icons/device.svg"
                checked: navigation.currentIndex === 0
                onClicked: navigation.currentIndex = 0
            }

            /*
            SL.IconTabButton {
                width: parent.width
                text: qsTr("Settings")
                iconSource: "qrc:/icons/service.svg"
                checked: navigation.currentIndex === 0
                onClicked: navigation.currentIndex = 0
            }
            */

            SL.IconTabButton {
                width: parent.width
                text: qsTr("Scan")
                iconSource: "qrc:/icons/scan.svg"
                checked: navigation.currentIndex === 1
                onClicked: navigation.currentIndex = 1
            }
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

            /*
            SL.SettingsPage {
                active: navigation.currentIndex === 0
            }
            */

            SL.ScanPage {
                active: navigation.currentIndex === 1
            }
        }

        SL.StatusBar {
            id: statusBar
            Layout.fillWidth: true
            Layout.preferredHeight: 32
        }
    }
}
