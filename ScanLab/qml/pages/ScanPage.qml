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

            SL.TabButton {
                text: qsTr("A-Scan")
            }

            SL.TabButton {
                text: qsTr("B-Scan")
            }

            SL.TabButton {
                text: qsTr("C-Scyn")
            }
        }

        SwipeView {
            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            SL.ScanAPage {}

            SL.ScanBPage {}

            SL.ScanCPage {}
        }
    }
}
