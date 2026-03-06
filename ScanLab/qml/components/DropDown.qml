import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL
import "." as App

Item {
    id: root

    property string label: ""
    property int labelWidth: 160

    property string infoText: ""
    property alias infoIconSource: infoIcon.iconSource
    property alias infoIconSize: infoIcon.size

    property var model: []

    // наружу отдаём именно enum value
    property int currentValue: -1

    // индекс вычисляем из currentValue
    readonly property int currentIndex: indexOfValue(currentValue)
    readonly property string currentText:
        currentIndex >= 0 && currentIndex < model.length
            ? model[currentIndex].text
            : ""

    signal activated(int value)

    property int fieldWidth: 280
    property int fieldHeight: 36

    property int radius: 8
    property int rowHeight: 36
    property int maxPopupHeight: 240

    implicitHeight: fieldHeight

    function indexOfValue(value) {
        for (let i = 0; i < model.length; ++i) {
            if (model[i].value === value)
                return i
        }
        return -1
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Label {
            visible: root.label.length > 0
            text: root.label
            font.pixelSize: SL.Theme.typography.fontSizeMd
            color: SL.Theme.colors.textPrimary
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight

            Layout.preferredWidth: root.labelWidth
            Layout.alignment: Qt.AlignVCenter
        }

        ComboBox {
            id: combo

            Layout.preferredWidth: root.fieldWidth
            Layout.preferredHeight: root.fieldHeight
            Layout.alignment: Qt.AlignVCenter

            model: root.model
            textRole: "text"

            Component.onCompleted: {
                combo.currentIndex = root.currentIndex
            }

            onActivated: function(index) {
                if (index >= 0 && index < root.model.length) {
                    root.currentValue = root.model[index].value
                    root.activated(root.currentValue)
                }
            }

            Connections {
                target: root
                function onCurrentValueChanged() {
                    const idx = root.indexOfValue(root.currentValue)
                    if (combo.currentIndex !== idx)
                        combo.currentIndex = idx
                }
            }

            hoverEnabled: true
            implicitHeight: root.fieldHeight

            background: Rectangle {
                radius: root.radius
                color: SL.Theme.colors.controlBackground
                border.width: 1
                border.color: combo.hovered
                              ? (SL.Theme.colors.borderStrong ?? SL.Theme.colors.border)
                              : SL.Theme.colors.border
                opacity: combo.down ? 0.92 : 1.0
            }

            contentItem: Text {
                leftPadding: 12
                rightPadding: 28
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight

                text: combo.currentText
                color: SL.Theme.colors.textPrimary
                font.pixelSize: SL.Theme.typography.fontSizeMd
            }

            indicator: Text {
                text: "\u25BE"
                color: SL.Theme.colors.textPrimary
                opacity: 0.9
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 12
            }

            popup: Popup {
                y: combo.height + 6
                width: combo.width
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
                    implicitHeight: contentHeight
                    model: combo.popup.visible ? combo.delegateModel : null

                    ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }

                    delegate: Item {
                        width: ListView.view.width
                        height: root.rowHeight

                        readonly property bool isSelected: index === combo.currentIndex

                        Rectangle {
                            anchors.fill: parent
                            radius: 6
                            color: isSelected
                                   ? SL.Theme.colors.controlChecked
                                   : (ma.containsMouse ? SL.Theme.colors.controlHovered : "transparent")
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            elide: Text.ElideRight

                            text: (modelData && modelData.text) ? modelData.text : ""
                            color: SL.Theme.colors.textPrimary
                            font.pixelSize: SL.Theme.typography.fontSizeMd
                        }

                        MouseArea {
                            id: ma
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                combo.currentIndex = index
                                root.currentValue = root.model[index].value
                                root.activated(root.currentValue)
                                combo.popup.close()
                            }
                        }
                    }
                }
            }
        }

        SL.InfoIcon {
            id: infoIcon
            visible: root.infoText.length > 0
            text: root.infoText

            Layout.preferredWidth: root.infoIconSize + 8
            Layout.preferredHeight: root.fieldHeight
        }
    }
}
