import QtQuick
import QtQuick.Controls
import ScanLab as SL

Item {
    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: true
    }

    Text {
        text: qsTr("Starting ScanLab...")
        anchors.top: busyIndicator.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 12
        font.pixelSize: 24
        color: SL.Theme.colors.textPrimary
    }

    Text {
        text: "ver. 0.0.1"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        font.pixelSize: 12
        color: SL.Theme.colors.textSecondary
        opacity: 0.6
    }
}
