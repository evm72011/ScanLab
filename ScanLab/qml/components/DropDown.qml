import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    id: root

    property string label: ""
    property int labelWidth: 160

    property string infoText: ""
    property alias infoIconSource: infoIcon.iconSource
    property alias infoIconSize: infoIcon.size

    property var model: []
    property int currentIndex: combo.currentIndex
    readonly property string currentText: combo.currentText

    signal activated(int index)

    property int fieldWidth: 280
    property int fieldHeight: 36

    property int radius: 8
    property int rowHeight: 36
    property int maxPopupHeight: 240

    implicitHeight: fieldHeight
    implicitWidth: (label.length > 0 ? labelWidth + 10 : 0)
                   + fieldWidth
                   + (infoText.length > 0 ? (infoIconSize + 8) : 0)

    RowLayout {
        anchors.fill: parent
        spacing: 10

        // === Left label ===
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

        // === ComboBox Field ===
        ComboBox {
            id: combo

            Layout.preferredWidth: root.fieldWidth
            Layout.preferredHeight: root.fieldHeight
            Layout.alignment: Qt.AlignVCenter

            model: root.model

            // синхронизация currentIndex наружу/внутрь
            // (чтобы root.currentIndex можно было задавать извне)
            onCurrentIndexChanged: {
                if (root.currentIndex !== combo.currentIndex)
                    root.currentIndex = combo.currentIndex
                root.activated(combo.currentIndex)
            }
            Component.onCompleted: {
                if (root.currentIndex !== combo.currentIndex)
                    combo.currentIndex = root.currentIndex
            }
            Connections {
                target: root
                function onCurrentIndexChanged() {
                    if (combo.currentIndex !== root.currentIndex)
                        combo.currentIndex = root.currentIndex
                }
            }

            // ====== Look & feel ======
            hoverEnabled: true
            implicitHeight: root.fieldHeight

            // фон поля
            background: Rectangle {
                id: bg
                radius: root.radius
                color: SL.Theme.colors.controlBackground
                border.width: 1
                border.color: combo.hovered
                              ? (SL.Theme.colors.borderStrong ?? SL.Theme.colors.border)
                              : SL.Theme.colors.border

                // лёгкая "pressed" индикация
                opacity: combo.down ? 0.92 : 1.0
            }

            // текст в поле
            contentItem: Text {
                leftPadding: 12
                rightPadding: 28 // место под стрелку
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight

                text: combo.currentText
                color: SL.Theme.colors.textPrimary
                font.pixelSize: SL.Theme.typography.fontSizeMd
            }

            // стрелка справа (indicator)
            indicator: Text {
                text: "\u25BE" // ▾
                color: SL.Theme.colors.textPrimary
                opacity: 0.9
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 12
            }

            // ====== Popup со списком ======
            popup: Popup {
                y: combo.height + 6
                width: combo.width
                padding: 6
                modal: false
                focus: true
                closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

                // ограничение по высоте
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

                    // используем стандартный delegate ComboBox, но рисуем свой
                    delegate: Item {
                        width: ListView.view.width
                        height: root.rowHeight

                        readonly property bool isSelected: (index === combo.currentIndex)

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

                            // modelData будет работать для массива строк;
                            // для ListModel можно использовать display/textRole (см. ниже)
                            text: (typeof modelData === "string") ? modelData : (modelData.display ?? modelData.text ?? "")
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
                                combo.popup.close()
                            }
                        }
                    }
                }
            }
        }

        // === Right info icon ===
        SL.InfoIcon {
            id: infoIcon
            visible: root.infoText.length > 0
            text: root.infoText

            Layout.preferredWidth: root.infoIconSize + 8
            Layout.preferredHeight: root.fieldHeight
        }
    }
}
