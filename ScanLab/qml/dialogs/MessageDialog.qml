import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

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

    property string shortText: ""
    property string detailsText: ""

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
        implicitHeight: contentColumn.implicitHeight + 32

        RowLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 16

            Item {
                Layout.alignment: Qt.AlignTop
                Layout.preferredWidth: 36
                Layout.preferredHeight: 36

                Image {
                    anchors.centerIn: parent
                    width: 28
                    height: 28
                    source: root.iconSource
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    mipmap: true
                }
            }

            ColumnLayout {
                id: contentColumn
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 10

                Label {
                    Layout.fillWidth: true
                    text: root.shortText
                    wrapMode: Text.Wrap
                    font.pixelSize: 18
                    font.bold: true
                    color: SL.Theme.colors.textPrimary
                }

                Text {
                    Layout.fillWidth: true
                    text: root.detailsText
                    wrapMode: Text.Wrap
                    font.pixelSize: 14
                    color: SL.Theme.colors.textPrimary
                }

                Item {
                    Layout.fillHeight: true
                    Layout.minimumHeight: 8
                }

                RowLayout {
                    Layout.alignment: Qt.AlignRight
                    spacing: 8

                    SL.Button {
                        text: "OK"
                        onClicked: root.close()
                    }
                }
            }
        }
    }
}
