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

    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnEscape

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
                implicitHeight: Math.max(48, titleLabel.implicitHeight + 24)
                color: "transparent"
                border.width: 0

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
                    anchors.rightMargin: 16
                    anchors.topMargin: 8
                    anchors.bottomMargin: 8
                    spacing: 16

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
                            smooth: true
                            mipmap: true
                        }
                    }

                    Label {
                        id: titleLabel
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter
                        text: root.dialogTitle
                        visible: text.length > 0
                        wrapMode: Text.Wrap
                        font.pixelSize: 14
                        font.bold: true
                        color: SL.Theme.colors.textPrimary
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
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    text: root.shortText
                    visible: text.length > 0
                    wrapMode: Text.Wrap
                    font.pixelSize: 14
                    color: SL.Theme.colors.textPrimary
                }

                Text {
                    Layout.fillWidth: true
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    text: root.detailsText
                    visible: text.length > 0
                    wrapMode: Text.Wrap
                    font.pixelSize: 14
                    color: SL.Theme.colors.textSecondary
                }

                Text {
                    Layout.fillWidth: true
                    Layout.topMargin: 24
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
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