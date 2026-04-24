import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

ToolButton {
    id: root

    property alias iconSource: root.icon.source
    property int iconSize: 20
    property bool active: false

    signal activated()

    Layout.preferredWidth: 30
    Layout.preferredHeight: 30
    Layout.minimumWidth: 30
    Layout.minimumHeight: 30
    Layout.maximumWidth: 30
    Layout.maximumHeight: 30

    checkable: true
    checked: active

    icon.width: root.iconSize
    icon.height: root.iconSize

    background: Rectangle {
        radius: 6
        color: //root.checked
               //? SL.Theme.colors.controlChecked
               root.hovered
                 ? SL.Theme.colors.controlHovered
                 : SL.Theme.colors.controlBackground
    }

    onClicked: root.activated()
}