import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import ScanLab 1.0 as SL

TabButton {
    id: root

    property url iconSource: ""
    property int iconSize: 32

    width: 96
    hoverEnabled: true

    background: Rectangle {
        anchors.fill: parent
        radius: 10
        color: root.down ? SL.Theme.colors.controlDown
             : root.checked ? SL.Theme.colors.controlChecked
             : root.hovered ? SL.Theme.colors.controlHovered
             : "transparent"
    }

    contentItem: Column {
        width: root.width
        anchors.centerIn: parent
        spacing: 4

        Image {
            id: iconImage
            width: root.iconSize
            height: root.iconSize
            source: root.iconSource
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: parent.horizontalCenter
            visible: false
            opacity: root.enabled ? (root.hovered || root.checked ? 1.0 : 0.85) : 0.4
        }

        MultiEffect {
            width: root.iconSize
            height: root.iconSize
            anchors.horizontalCenter: parent.horizontalCenter
            source: iconImage
            colorization: 1.0
            colorizationColor: SL.Theme.colors.toolbarIcon
            opacity: iconImage.opacity
        }

        Text {
            text: root.text
            font.pixelSize: 12
            font.bold: true
            color: (root.hovered || root.checked)
                   ? SL.Theme.colors.controlActiveText
                   : SL.Theme.colors.controlNormalText
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }
    }
}
