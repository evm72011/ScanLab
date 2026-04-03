import QtQuick
import QtQuick.Controls
import ScanLab as SL

Item {
    id: root

    property string text: ""
    property url iconSource: "qrc:/icons/info.svg"
    property int size: 8

    implicitWidth: size
    implicitHeight: size

    Image {
        anchors.fill: parent
        source: root.iconSource
        visible: root.iconSource !== ""
        fillMode: Image.PreserveAspectFit
        smooth: true
    }

    Text {
        anchors.centerIn: parent
        visible: root.iconSource === ""
        text: "i"
        color: SL.Theme.colors.textSecondary
        font.pixelSize: root.size
        font.bold: true
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.WhatsThisCursor
        onEntered: tip.open()
        onExited: tip.close()
    }

    ToolTip {
        id: tip

        text: root.text
        visible: false
        delay: 250

        padding: 8

        background: Rectangle {
            radius: 6
            color: SL.Theme.colors.controlBackground
            border.color: SL.Theme.colors.border
            border.width: 1
        }

        contentItem: Text {
            text: tip.text
            color: SL.Theme.colors.textPrimary
            font.pixelSize: SL.Theme.typography.fontSizeSm
            wrapMode: Text.WordWrap
        }
    }
}
