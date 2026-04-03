import QtQuick
import QtQuick.Controls
import ScanLab as SL

Rectangle {
    id: root

    property url iconSource: ""
    property string text: ""
    property int iconSize: 14
    property real iconOpacity: 1
    property bool rotateIcon: false

    height: 30
    color: SL.Theme.colors.statusbarBackground

    implicitWidth: row.implicitWidth + 12

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
}
