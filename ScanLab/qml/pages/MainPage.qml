import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab

ColumnLayout {
    anchors.fill: parent
    spacing: 0

    TabBar {
        id: tabBar
        Layout.fillWidth: true

        IconTabButton {
            text: "Settings"
            iconSource: "qrc:/icons/service.svg"
            width: 96
        }

        IconTabButton {
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

        Rectangle {
            color: "#202020"
            Label { anchors.centerIn: parent; text: "Settings"; color: "white" }
        }

        Rectangle {
            color: "#303030"
            Label { anchors.centerIn: parent; text: "Scan"; color: "white" }
        }
    }

    StatusBar {
        id: statusBar
        Layout.fillWidth: true
        Layout.preferredHeight: 32
    }
}
