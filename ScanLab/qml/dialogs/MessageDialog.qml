import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Dialog {
    id: root

    enum Type {
        Info,
        Warning,
        Error
    }

    property int messageType: Type.Error

    readonly property url iconSource: {
        switch (messageType) {
        case MessageDialog.Type.Info: return "qrc:/icons/information.svg"
        case MessageDialog.Type.Warning: return "qrc:/icons/warning.svg"
        case MessageDialog.Type.Error: return "qrc:/icons/error.svg"
        }
    }

    property string dialogTitle: ""
    property string shortText: ""
    property string detailsText: ""
    property string errorCode: ""

    modal: true
    focus: true
    padding: 0
    width: 520

    parent: Overlay.overlay
    closePolicy: Popup.CloseOnEscape

    function centerInOverlay() {
        if (!parent)
            return

        const pw = parent.width
        const ph = parent.height
        const w = width
        const h = height

        if (!Number.isFinite(pw) || !Number.isFinite(ph) ||
            !Number.isFinite(w) || !Number.isFinite(h) ||
            pw <= 0 || ph <= 0 || w <= 0 || h <= 0) {
            return
        }

        x = (pw - w) / 2
        y = (ph - h) / 2
    }

    onOpened: centerInOverlay()

    background: Rectangle {
        radius: 12
        color: SL.Theme.colors.windowBackground
        border.width: 1
        border.color: SL.Theme.colors.border
    }

    contentItem: Item {
        implicitWidth: 520
        implicitHeight: contentColumn.implicitHeight

        ColumnLayout {
            id: contentColumn
            anchors.fill: parent
            spacing: 0

            Rectangle {
                id: header
                Layout.fillWidth: true
                implicitHeight: 56
                color: "transparent"
                border.width: 0

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 1
                    color: SL.Theme.colors.border
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.SizeAllCursor

                    property real pressX: 0
                    property real pressY: 0
                    property real startX: 0
                    property real startY: 0

                    onPressed: function(mouse) {
                        const p = mapToItem(root.parent, mouse.x, mouse.y)
                        pressX = p.x
                        pressY = p.y
                        startX = root.x
                        startY = root.y
                    }

                    onPositionChanged: function(mouse) {
                        if (!pressed || !root.parent)
                            return

                        const p = mapToItem(root.parent, mouse.x, mouse.y)

                        let newX = startX + (p.x - pressX)
                        let newY = startY + (p.y - pressY)

                        const maxX = Math.max(0, root.parent.width - root.width)
                        const maxY = Math.max(0, root.parent.height - root.height)

                        root.x = Math.max(0, Math.min(maxX, newX))
                        root.y = Math.max(0, Math.min(maxY, newY))
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 8   // чуть меньше, чтобы X ближе к краю
                    anchors.topMargin: 8
                    anchors.bottomMargin: 8
                    spacing: 12

                    Item {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.preferredWidth: 28
                        Layout.preferredHeight: 28

                        Image {
                            anchors.centerIn: parent
                            width: 20
                            height: 20
                            source: root.iconSource
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Label {
                        Layout.alignment: Qt.AlignVCenter
                        text: root.dialogTitle
                        visible: text.length > 0
                        wrapMode: Text.Wrap
                        font.pixelSize: 16
                        font.bold: true
                        color: SL.Theme.colors.textPrimary
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    ToolButton {
                        id: closeButton
                        width: 28
                        height: 28

                        HoverHandler {
                            cursorShape: Qt.PointingHandCursor
                        }

                        contentItem: Text {
                            text: "✕"
                            font.pixelSize: 18
                            anchors.centerIn: parent
                            color: SL.Theme.colors.textSecondary
                        }

                        background: Rectangle {
                            anchors.fill: parent
                            radius: 6
                            color: closeButton.hovered
                                   ? SL.Theme.colors.controlHovered
                                   : "transparent"
                        }

                        onClicked: root.close()
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 10

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 16
                }

                Text {
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 16
                    text: root.shortText
                    visible: text.length > 0
                    wrapMode: Text.Wrap
                    font.pixelSize: 16
                    color: SL.Theme.colors.textPrimary
                }

                Text {
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 16
                    text: root.detailsText
                    visible: text.length > 0
                    wrapMode: Text.Wrap
                    font.pixelSize: 16
                    color: SL.Theme.colors.textSecondary
                }

                Text {
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 16
                    Layout.topMargin: 8
                    text: root.errorCode.length > 0
                          ? qsTr("Error code: %1").arg(root.errorCode)
                          : ""
                    visible: root.errorCode.length > 0
                    wrapMode: Text.Wrap
                    font.pixelSize: 12
                    color: SL.Theme.colors.textSecondary
                    font.family: "monospace"
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    Layout.topMargin: 12
                    Layout.bottomMargin: 16

                    Item {
                        Layout.fillWidth: true
                    }

                    SL.Button {
                        text: qsTr("OK")
                        onClicked: root.close()
                    }
                }
            }
        }
    }
}