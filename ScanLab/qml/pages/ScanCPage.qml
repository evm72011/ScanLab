import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    Rectangle {
        anchors.fill: parent
        color: SL.Theme.colors.windowBackground

        Label {
            anchors.centerIn: parent
            text: qsTr("C-Scan placeholder")
            color: SL.Theme.colors.textPrimary
        }
    }
}
