import QtQuick
import QtQuick.Controls
import ScanLab as SL

Item {
    id: root

    readonly property var appInfo: backend?.appInfo ?? null

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: true
    }

    Text {
        text: qsTr("Starting %1...").arg(appInfo?.name ?? "foo")
        anchors.top: busyIndicator.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 12
        font.pixelSize: 24
        color: SL.Theme.colors.textPrimary
    }

    Text {
        text: "ver. " + (appInfo?.version ?? "?.?.?")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        font.pixelSize: 12
        color: SL.Theme.colors.textSecondary
        opacity: 0.6
    }
}
