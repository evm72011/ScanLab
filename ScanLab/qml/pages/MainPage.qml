import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

ColumnLayout {
    anchors.fill: parent
    spacing: 0

    TabBar {
        id: tabBar
        Layout.fillWidth: true

        SL.IconTabButton {
            text: "Settings"
            iconSource: "qrc:/icons/service.svg"
            width: 96
        }

        SL.IconTabButton {
            text: "Scan"
            iconSource: "qrc:/icons/scan.svg"
            width: 96
        }
    }

    SwipeView {
        id: swipeView
        Layout.fillWidth: true
        Layout.fillHeight: true

        interactive: false

        currentIndex: tabBar.currentIndex

        SL.SettingsPage { }

        SL.ScanPage { }
    }

    SL.StatusBar {
        id: statusBar
        Layout.fillWidth: true
        Layout.preferredHeight: 32
    }
}
