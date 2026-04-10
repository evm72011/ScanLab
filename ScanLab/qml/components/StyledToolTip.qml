import QtQuick
import QtQuick.Controls
import ScanLab as SL

ToolTip {
    id: root

    delay: 250
    padding: 8

    background: Rectangle {
        radius: 6
        color: SL.Theme.colors.controlBackground
        border.color: SL.Theme.colors.border
        border.width: 1
    }

    contentItem: Text {
        text: root.text
        color: SL.Theme.colors.textPrimary
        font.pixelSize: SL.Theme.typography.fontSizeSm
        wrapMode: Text.WordWrap
    }
}
