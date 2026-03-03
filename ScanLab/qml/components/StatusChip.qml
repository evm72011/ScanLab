import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    property url iconSource: ""
    property string text: ""
    property int iconSize: 14

    height: 30
    color: "#161616"
    //border.color: "#2a2a2a"
    //border.width: 1

    // чтобы не было "половина иконки"
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
            color: "#eaeaea"
            font.pixelSize: 12
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }
}
