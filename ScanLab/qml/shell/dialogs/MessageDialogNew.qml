import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Dialog {
    id: root

    property url iconSource: ""
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

        if (pw <= 0 || ph <= 0 || width <= 0 || height <= 0)
            return

        x = (pw - width) / 2
        y = (ph - height) / 2
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
                Layout.fillWidth: true
                implicitHeight: 56
                color: "transparent"

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 1
                    color: SL.Theme.colors.border
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 8
                    anchors.topMargin: 8
                    anchors.bottomMargin: 8
                    spacing: 12

                    Image {
                        Layout.alignment: Qt.AlignVCenter
                        width: 20
                        height: 20
                        source: root.iconSource
                        fillMode: Image.PreserveAspectFit
                        visible: root.iconSource.toString().length > 0
                    }

                    Label {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.fillWidth: true
                        text: root.dialogTitle
                        visible: text.length > 0
                        wrapMode: Text.Wrap
                        font.pixelSize: 16
                        font.bold: true
                        color: SL.Theme.colors.textPrimary
                    }

                    ToolButton {
                        id: closeButton
                        width: 28
                        height: 28

                        contentItem: Image {
                            source: "qrc:/icons/close.svg"
                            width: 14
                            height: 14
                            sourceSize.width: 14
                            sourceSize.height: 14
                            opacity: closeButton.hovered ? 1.0 : 0.75
                            anchors.centerIn: parent
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