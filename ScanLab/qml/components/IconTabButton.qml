import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import ScanLab 1.0 as SL

TabButton {
    id: root

    property url iconSource: ""
    property int iconSize: 32
    property color normalTextColor: "#D0D7DE"
    property color activeTextColor: "white"
    property color iconColor: SL.Theme.colors.toolbarIcon

    width: 96
    hoverEnabled: true

    background: Rectangle {
        anchors.fill: parent
        radius: 10
        color: root.down ? "#3B536A"
             : root.checked ? "#34495E"
             : root.hovered ? "#3A5068"
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
            visible: false                    // важно
            opacity: root.enabled ? (root.hovered || root.checked ? 1.0 : 0.85) : 0.4
        }

        MultiEffect {
            width: root.iconSize
            height: root.iconSize
            anchors.horizontalCenter: parent.horizontalCenter
            source: iconImage
            colorization: 1.0
            colorizationColor: root.iconColor
            opacity: iconImage.opacity        // переносим твою логику enabled/hover
        }

        Text {
            text: root.text
            font.pixelSize: 12
            font.bold: true
            color: (root.hovered || root.checked) ? root.activeTextColor : root.normalTextColor
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }
    }
}
