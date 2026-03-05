import QtQuick
import QtQuick.Controls
import ScanLab 1.0 as SL

Rectangle {
    id: root

    property string text: ""
    property url iconSource: ""
    property int iconSize: 16
    property int cornerRadius: 10

    signal clicked()

    implicitWidth: Math.max(120, textItem.implicitWidth + 32)
    implicitHeight: 40

    radius: cornerRadius

    color: ma.pressed ? SL.Theme.colors.controlDown
         : ma.containsMouse ? SL.Theme.colors.controlHovered
         : SL.Theme.colors.controlBackground

    border.width: 1
    border.color: SL.Theme.colors.border

    Text {
        id: textItem
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: SL.Theme.typography.fontSizeMd
        color: SL.Theme.colors.textPrimary
    }

    Image {
        visible: iconSource !== ""
        source: iconSource
        width: iconSize
        height: iconSize
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: textItem.left
        anchors.rightMargin: 6
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
