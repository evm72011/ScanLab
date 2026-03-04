import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    ColumnLayout {
        width: parent ? parent.width : 0
        height: parent ? parent.height : 0
        spacing: 0

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Hardware")
                width: 96
                hoverEnabled: true
            }
            TabButton {
                text: qsTr("Scan")
                width: 96
                hoverEnabled: true
            }
        }

        SwipeView {
            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            SL.HardwarePage {}

            Rectangle {
                color: SL.Theme.colors.windowBackground
                Label {
                    anchors.centerIn: parent
                    text: qsTr("Bar")
                    color: SL.Theme.colors.textPrimary
                }
            }
        }
    }
}
