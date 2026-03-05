import QtQuick
import ScanLab 1.0 as SL

Rectangle {
    id: root

    property string text: ""
    property url iconSource: ""
    property int iconSize: 16
    property int cornerRadius: 10

    signal clicked()

    width: 120
    height: 40
    radius: cornerRadius

    color: ma.pressed ? SL.Theme.colors.controlDown
         : ma.containsMouse ? SL.Theme.colors.controlHovered
         : SL.Theme.colors.controlBackground

    border.width: 1
    border.color: SL.Theme.colors.border

    // текст всегда по центру
    Text {
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: SL.Theme.typography.fontSizeMd
        color: SL.Theme.colors.textPrimary
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    // иконка слева, если задана
    Image {
        visible: root.iconSource !== ""
        source: root.iconSource
        width: root.iconSize
        height: root.iconSize
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
        smooth: true
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
