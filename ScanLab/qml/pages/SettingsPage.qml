import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    property bool active: false

    ColumnLayout {
        width: parent ? parent.width : 0
        height: parent ? parent.height : 0
        spacing: 0

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            SL.TabButton {
                text: qsTr("Hardware")
            }

            SL.TabButton {
                text: qsTr("Scan")
            }

            SL.TabButton {
                text: qsTr("Foo")
            }
        }

        SwipeView {
            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex
            interactive: false

            SL.HardwarePage {}

            Rectangle {
                color: SL.Theme.colors.windowBackground
                Label {
                    anchors.centerIn: parent
                    text: qsTr("Scan")
                    color: SL.Theme.colors.textPrimary
                }
            }

            Rectangle {
                color: SL.Theme.colors.windowBackground
                Label {
                    anchors.centerIn: parent
                    text: qsTr("Foo")
                    color: SL.Theme.colors.textPrimary
                }
            }
        }
    }
}
