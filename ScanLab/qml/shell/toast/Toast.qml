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

    width: 400
    implicitHeight: Math.max(96, content.implicitHeight + 28)

    radius: 0
    color: SL.Theme.colors.windowBackground
    border.color: SL.Theme.colors.border
    opacity: 0

    RowLayout {
        id: content

        anchors.fill: parent
        anchors.margins: 14
        anchors.rightMargin: 42
        spacing: 14

        Image {
            Layout.alignment: Qt.AlignTop
            source: root.iconSource
            sourceSize.width: 28
            sourceSize.height: 28
            width: 28
            height: 28
            visible: root.iconSource.length > 0
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            spacing: 6

            Text {
                Layout.fillWidth: true
                text: root.titleText
                font.bold: true
                font.pixelSize: 16
                color: SL.Theme.colors.textPrimary
                wrapMode: Text.Wrap
            }

            Text {
                Layout.fillWidth: true
                text: root.bodyText
                font.pixelSize: 14
                color: SL.Theme.colors.textSecondary
                wrapMode: Text.Wrap
                visible: root.bodyText.length > 0
            }
        }
    }

    Button {
        id: closeButton

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 6
        anchors.rightMargin: 6

        width: 28
        height: 28
        text: "×"

        onClicked: {
            fadeOut.start()
        }
    }

    SequentialAnimation {
        id: fadeIn

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

        ScriptAction {
            script: {
                if (root.durationMs > 0) {
                    fadeOut.start()
                }
            }
        }
    }

    SequentialAnimation {
        id: fadeOut

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