import QtQuick
import ScanLab 1.0 as SL

Rectangle {
    id: root

    property string text: ""
    property url iconSource: ""
    property int iconSize: 16
    property int cornerRadius: 10
    property bool busy: false

    signal clicked()

    width: 120
    height: 40
    radius: cornerRadius

    color: !root.enabled
         ? SL.Theme.colors.controlBackground
         : ma.pressed
            ? SL.Theme.colors.controlDown
            : ma.containsMouse
                ? SL.Theme.colors.controlHovered
                : SL.Theme.colors.controlBackground

    border.width: 1
    border.color: SL.Theme.colors.border

    opacity: root.enabled ? 1.0 : 0.55

    Text {
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: SL.Theme.typography.fontSizeMd
        color: SL.Theme.colors.textPrimary
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Image {
        id: icon

        visible: root.iconSource !== "" || root.busy
        source: root.busy ? "qrc:/icons/update.svg" : root.iconSource

        width: root.iconSize
        height: root.iconSize

        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.verticalCenter: parent.verticalCenter

        fillMode: Image.PreserveAspectFit
        smooth: true
        opacity: root.enabled ? 1.0 : 0.35

        transformOrigin: Item.Center

        RotationAnimator on rotation {
            running: root.busy
            from: 0
            to: 360
            duration: 900
            loops: Animation.Infinite
        }
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        enabled: root.enabled && !root.busy
        hoverEnabled: root.enabled && !root.busy
        cursorShape: (root.enabled && !root.busy)
            ? Qt.PointingHandCursor
            : Qt.ArrowCursor

        onClicked: root.clicked()
    }
}
