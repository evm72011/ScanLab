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
                font.pixelSize: SL.Theme.typography.fontSizeMd
                color: SL.Theme.colors.textPrimary
                wrapMode: Text.Wrap
            }

            Text {
                Layout.fillWidth: true
                text: root.bodyText
                font.pixelSize: SL.Theme.typography.fontSizeSm
                color: SL.Theme.colors.textSecondary
                wrapMode: Text.Wrap
                visible: root.bodyText.length > 0
            }
        }
    }
    HoverHandler {
        id: hoverHandler

        onHoveredChanged: {
            if (root.durationMs <= 0 || root.closing) {
                return
            }

            if (hovered) {
                autoCloseTimer.stop()
            } else {
                autoCloseTimer.restart()
            }
        }
    }

    Timer {
        id: autoCloseTimer

        interval: root.durationMs
        running: root.durationMs > 0
        repeat: false

        onTriggered: {
            fadeOut.start()
        }
    }

    NumberAnimation {
        id: fadeIn

        target: root
        property: "opacity"
        from: 0
        to: 1
        duration: 180
        running: true
    }

    SequentialAnimation {
        id: fadeOut

        ScriptAction {
            script: root.closing = true
        }

        NumberAnimation {
            target: root
            property: "opacity"
            from: root.opacity
            to: 0
            duration: 700
        }

        ScriptAction {
            script: root.expired()
        }
    }

    Rectangle {
        id: closeButton

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 6
        anchors.rightMargin: 6

        width: 28
        height: 28

        radius: 0
        color: mouseArea.containsMouse
               ? Qt.rgba(1, 1, 1, 0.08)
               : "transparent"

        Image {
            anchors.centerIn: parent

            source: "qrc:/icons/close.svg"

            width: 14
            height: 14

            sourceSize.width: 14
            sourceSize.height: 14

            opacity: mouseArea.containsMouse ? 1.0 : 0.75
        }

        MouseArea {
            id: mouseArea

            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                autoCloseTimer.stop()
                fadeOut.start()
            }
        }
    }
}
