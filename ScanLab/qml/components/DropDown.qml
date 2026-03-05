import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    id: root

    property string label: ""
    property int labelWidth: 160

    property bool showInfo: false
    property string infoText: ""
    property url infoIconSource: "qrc:/icons/info.svg"
    property int infoIconSize: 16

    property var model: []
    property int currentIndex: 0
    readonly property string currentText:
        (Array.isArray(model) && model.length > 0
         && currentIndex >= 0 && currentIndex < model.length)
            ? model[currentIndex]
            : ""

    signal activated(int index)

    property int fieldWidth: 280
    property int fieldHeight: 36

    property int radius: 8
    property int rowHeight: 36
    property int maxPopupHeight: 240

    implicitHeight: fieldHeight
    implicitWidth: (label.length > 0 ? labelWidth + 10 : 0)
                   + fieldWidth
                   + (showInfo ? (infoIconSize + 8) : 0)

    RowLayout {
        anchors.fill: parent
        spacing: 10

        // === Left label ===
        Label {
            visible: root.label.length > 0
            text: root.label
            color: SL.Theme.colors.textPrimary
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight

            Layout.preferredWidth: root.labelWidth
            Layout.alignment: Qt.AlignVCenter
        }

        // === Field ===
        Item {
            id: fieldHost
            Layout.preferredWidth: root.fieldWidth
            Layout.preferredHeight: root.fieldHeight
            Layout.alignment: Qt.AlignVCenter

            Rectangle {
                id: field
                anchors.fill: parent
                radius: root.radius
                color: SL.Theme.colors.controlBackground
                border.color: SL.Theme.colors.border
                border.width: 1
            }

            Text {
                id: valueText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 12
                anchors.right: indicator.left
                anchors.rightMargin: 8
                text: root.currentText
                color: SL.Theme.colors.textPrimary
                elide: Text.ElideRight
            }

            Text {
                id: indicator
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 12
                text: "\u25BE" // ▾
                color: SL.Theme.colors.textPrimary
                opacity: 0.9
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: popup.open()

                onEntered: field.border.color = SL.Theme.colors.borderStrong ?? SL.Theme.colors.border
                onExited: field.border.color = SL.Theme.colors.border
            }

            Popup {
                id: popup
                x: 0
                y: fieldHost.height + 6
                width: fieldHost.width

                padding: 6
                modal: false
                focus: true
                closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

                implicitHeight: Math.min(list.contentHeight + padding * 2, root.maxPopupHeight)

                background: Rectangle {
                    radius: root.radius
                    color: SL.Theme.colors.controlBackground
                    border.color: SL.Theme.colors.border
                    border.width: 1
                }

                contentItem: ListView {
                    id: list
                    clip: true
                    model: root.model
                    currentIndex: root.currentIndex
                    implicitHeight: contentHeight

                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AsNeeded
                    }

                    delegate: Item {
                        width: ListView.view.width
                        height: root.rowHeight

                        Rectangle {
                            anchors.fill: parent
                            radius: 6
                            color: (index === root.currentIndex)
                                   ? SL.Theme.colors.controlChecked
                                   : (ma.containsMouse ? SL.Theme.colors.controlHovered : "transparent")
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            text: modelData
                            color: SL.Theme.colors.textPrimary
                            elide: Text.ElideRight
                        }

                        MouseArea {
                            id: ma
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                root.currentIndex = index
                                root.activated(index)
                                popup.close()
                            }
                        }
                    }
                }
            }
        }

        // === Right info icon ===
        Item {
            visible: root.showInfo
            Layout.preferredWidth: root.showInfo ? (root.infoIconSize + 8) : 0
            Layout.preferredHeight: root.fieldHeight
            Layout.alignment: Qt.AlignVCenter

            Item {
                anchors.centerIn: parent
                width: root.infoIconSize
                height: root.infoIconSize

                Image {
                    anchors.fill: parent
                    source: root.infoIconSource
                    visible: root.infoIconSource !== ""
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }

                Text {
                    anchors.centerIn: parent
                    visible: root.infoIconSource === ""
                    text: "i"
                    color: SL.Theme.colors.textSecondary
                    font.pixelSize: root.infoIconSize
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
                    text: root.infoText
                    visible: false
                    delay: 250
                }
            }
        }
    }
}
