/*
import QtQuick
import QtQuick.Controls


SwipeView {
    id: swipeView
    interactive: false

    ConnectPage {
    }
}
*/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab

ColumnLayout {
    anchors.fill: parent
    spacing: 0

    // 🔹 Вкладки сверху
    TabBar {
        id: tabBar
        Layout.fillWidth: true

        IconTabButton {
            text: "Settings"
            iconSource: "qrc:/resources/icons/cog.svg"
            width: 96
        }

        IconTabButton {
            text: "Scan"
            iconSource: "qrc:/resources/icons/cog.svg"
            width: 96
        }
    }

    // 🔹 Контент
    SwipeView {
        id: swipeView
        Layout.fillWidth: true
        Layout.fillHeight: true

        interactive: false   // если не хочешь свайп мышкой

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
}
