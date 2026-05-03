import QtQuick
import QtQuick.Controls
import ScanLab as SL

Rectangle {
    id: root

    property url iconSource: ""
    property string text: ""
    property string tooltip: ""
    property int iconSize: 14
    property real iconOpacity: 1
    property bool rotateIcon: false
    property bool pulseBackground: false

    height: 30
    color: "transparent"
    implicitWidth: row.implicitWidth + 12

    Rectangle {
        id: pulseGlow
        anchors.fill: parent

        radius: 3
        color: Qt.rgba(1, 1, 1, 0.16)
        opacity: 0

        SequentialAnimation on opacity {
            running: root.pulseBackground
            loops: Animation.Infinite

            NumberAnimation { from: 0.0; to: 0.4; duration: 500 }
            NumberAnimation { from: 0.4; to: 0.0; duration: 500 }
        }
    }

    Row {
        id: row
        anchors.verticalCenter: parent.verticalCenter
        x: 6
        spacing: 6

        Image {
            id: icon
            visible: root.iconSource !== ""
            source: root.iconSource
            width: root.iconSize
            height: root.iconSize
            fillMode: Image.PreserveAspectFit
            smooth: true
            opacity: root.iconOpacity
            transformOrigin: Item.Center

            RotationAnimator on rotation {
                running: root.rotateIcon
                from: 0
                to: 360
                duration: 900
                loops: Animation.Infinite
            }
        }

        Text {
            text: root.text
            color: SL.Theme.colors.textPrimary
            font.pixelSize: 12
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }

    HoverHandler {
        id: hoverHandler
    }

    SL.StyledToolTip {
        text: root.tooltip
        visible: hoverHandler.hovered && root.tooltip != ""
    }

    Rectangle {
        anchors.fill: parent
        radius: 4
        color: hoverHandler.hovered ? Qt.rgba(1, 1, 1, 0.05) : "transparent"
    }
}
