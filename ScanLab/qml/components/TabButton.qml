import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import ScanLab as SL

TabButton {
    id: root

    font.pixelSize: SL.Theme.typography.fontSizeMd
    width: 96
    hoverEnabled: true
    height: 32

    background: Shape {
        anchors.fill: parent
        anchors.margins: 0.5
        ShapePath {
            strokeWidth: 1
            strokeColor: SL.Theme.colors.border

            fillColor : root.down ? SL.Theme.colors.controlDown
                      : root.checked ? SL.Theme.colors.tabChecked
                      : root.hovered ? SL.Theme.colors.controlHovered
                      : SL.Theme.colors.tabDefault

            /*
            fillColor: root.down ? SL.Theme.colors.controlDown
                      : root.checked ? SL.Theme.colors.controlChecked
                      : root.hovered ? SL.Theme.colors.controlHovered
                      : "transparent"
            */
            startX: 0; startY: height

            PathLine { x: 0; y: 6 }
            PathQuad { x: 6; y: 0; controlX: 0; controlY: 0 }

            PathLine { x: width - 6; y: 0 }
            PathQuad { x: width; y: 6; controlX: width; controlY: 0 }

            PathLine { x: width; y: height }
            PathLine { x: 0; y: height }
        }
    }

    contentItem: Text {
        text: root.text
        font.pixelSize: SL.Theme.typography.fontSizeMd
        font.bold: root.checked

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: root.checked
               ? SL.Theme.colors.textPrimary
               : SL.Theme.colors.textSecondary
    }
}
