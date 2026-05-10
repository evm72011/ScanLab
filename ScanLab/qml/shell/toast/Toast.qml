import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

    signal expired()

    property string titleText: ""
    property string bodyText: ""
    property string iconSource: ""
    property int durationMs: 3000

    width: 360
    implicitHeight: content.implicitHeight + 24

    radius: 8
    color: SL.Theme.colors.windowBackground
    border.color: SL.Theme.colors.border
    opacity: 0

    RowLayout {
        id: content

        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        Image {
            Layout.alignment: Qt.AlignTop
            source: root.iconSource
            sourceSize.width: 22
            sourceSize.height: 22
            width: 22
            height: 22
            visible: root.iconSource.length > 0
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Text {
                Layout.fillWidth: true
                text: root.titleText
                font.bold: true
                color: "white"
                wrapMode: Text.Wrap
            }

            Text {
                Layout.fillWidth: true
                text: root.bodyText
                color: "#cccccc"
                wrapMode: Text.Wrap
                visible: root.bodyText.length > 0
            }
        }
    }

    SequentialAnimation {
        running: true

        NumberAnimation {
            target: root
            property: "opacity"
            from: 0
            to: 1
            duration: 180
        }

        PauseAnimation {
            duration: root.durationMs
        }

        NumberAnimation {
            target: root
            property: "opacity"
            from: 1
            to: 0
            duration: 250
        }

        ScriptAction {
            script: root.expired()
        }
    }
}