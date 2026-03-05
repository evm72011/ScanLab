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

    // Главное свойство для binding снаружи (в т.ч. на C++)
    property string value: ""
    property string placeholderText: ""
    property bool readOnly: false
    property bool enabled: true

    property int fieldWidth: 280
    property int fieldHeight: 36
    property int radius: 8

    signal valueEdited(string value)      // пользователь набирает
    signal accepted(string value)
    signal editingFinished(string value)

    implicitHeight: fieldHeight
    implicitWidth: (label.length > 0 ? labelWidth + 10 : 0)
                   + fieldWidth
                   + (showInfo ? (infoIconSize + 8) : 0)

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

        TextField {
            id: field

            Layout.preferredWidth: root.fieldWidth
            Layout.preferredHeight: root.fieldHeight
            Layout.alignment: Qt.AlignVCenter

            enabled: root.enabled
            readOnly: root.readOnly
            placeholderText: root.placeholderText

            // 1) отображение значения
            text: root.value

            // 2) пользователь меняет -> пушим наружу
            onTextEdited: {
                if (root.value !== text)
                    root.value = text
                root.valueEdited(root.value)
            }

            onAccepted: root.accepted(root.value)
            onEditingFinished: root.editingFinished(root.value)

            // 3) если value меняется извне, но юзер сейчас печатает,
            //    не перетираем ввод. Обновляем поле, когда нет фокуса.
            Connections {
                target: root
                function onValueChanged() {
                    if (!field.activeFocus && field.text !== root.value)
                        field.text = root.value
                }
            }

            hoverEnabled: true
            implicitHeight: root.fieldHeight
            padding: 0

            background: Rectangle {
                radius: root.radius
                color: SL.Theme.colors.controlBackground
                border.width: 1
                border.color: field.hovered
                              ? (SL.Theme.colors.borderStrong ?? SL.Theme.colors.border)
                              : SL.Theme.colors.border
                opacity: field.down ? 0.92 : 1.0
            }

            font.pixelSize: SL.Theme.typography.fontSizeMd
            color: SL.Theme.colors.textPrimary
            leftPadding: 12
            rightPadding: 12
            verticalAlignment: Text.AlignVCenter
        }

        SL.InfoIcon {
            id: infoIcon
            visible: root.infoText.length > 0
            text: root.infoText

            Layout.preferredWidth: root.infoIconSize + 8
            Layout.preferredHeight: root.fieldHeight
            Layout.alignment: Qt.AlignVCenter
        }
    }
}
