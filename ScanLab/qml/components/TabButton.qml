import QtQuick
import QtQuick.Controls
import ScanLab 1.0 as SL

TabButton {
    id: root

    font.pixelSize: SL.Theme.typography.fontSizeMd
    width: 96
    hoverEnabled: true

    background: Rectangle {
        radius: 6
        color: root.down ? SL.Theme.colors.controlDown
             : root.checked ? SL.Theme.colors.controlChecked
             : root.hovered ? SL.Theme.colors.controlHovered
             : "transparent"
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
