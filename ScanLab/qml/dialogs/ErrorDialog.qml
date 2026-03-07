import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root

    property string shortText: ""
    property string detailsText: ""
    property url iconSource: "qrc:/qml/icons/error.svg"

    modal: true
    focus: true
    padding: 0
    width: 520

    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnEscape

    background: Rectangle {
        radius: 12
        color: "white"
        border.width: 1
        border.color: "#d6d6d6"
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
                    color: "#202020"
                }

                Text {
                    Layout.fillWidth: true
                    text: root.detailsText
                    wrapMode: Text.Wrap
                    font.pixelSize: 14
                    color: "#505050"
                }

                Item {
                    Layout.fillHeight: true
                    Layout.minimumHeight: 8
                }

                RowLayout {
                    Layout.alignment: Qt.AlignRight
                    spacing: 8

                    Button {
                        text: "OK"
                        onClicked: root.close()
                    }
                }
            }
        }
    }
}
