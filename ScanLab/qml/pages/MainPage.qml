import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

ColumnLayout {
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0
    spacing: 0

    TabBar {
        id: tabBar
        Layout.fillWidth: true

        SL.IconTabButton {
            text: qsTr("Settings")
            iconSource: "qrc:/icons/service.svg"
        }

        SL.IconTabButton {
            text: qsTr("Scan")
            iconSource: "qrc:/icons/scan.svg"
        }
    }

    Rectangle {
        Layout.fillWidth: true
        height: 1
        color: SL.Theme.colors.border
    }

    SwipeView {
        id: stack
        Layout.fillWidth: true
        Layout.fillHeight: true

        interactive: false

        currentIndex: tabBar.currentIndex

        SL.SettingsPage {
            active: stack.currentIndex === 0
        }

        SL.ScanPage {
            active: stack.currentIndex === 1
        }
    }

    SL.StatusBar {
        id: statusBar
        Layout.fillWidth: true
        Layout.preferredHeight: 32
    }
}
