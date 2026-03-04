import QtQuick
import QtQuick.Controls
import ScanLab 1.0 as SL

Rectangle {
    id: root

    property url iconSource: ""
    property string text: ""
    property int iconSize: 14

    height: 30
    color: SL.Theme.colors.statusbarBackground

    implicitWidth: row.implicitWidth + 12

    Row {
        id: row
        anchors.verticalCenter: parent.verticalCenter
        x: 6
        spacing: 6

        Image {
            visible: root.iconSource !== ""
            source: root.iconSource
            width: root.iconSize
            height: root.iconSize
            fillMode: Image.PreserveAspectFit
            smooth: true
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
