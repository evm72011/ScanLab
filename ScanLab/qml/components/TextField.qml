import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Item {
    id: root

    property string label: ""
    property int labelWidth: 160

    property string infoText: ""
    property alias infoIconSource: infoIcon.iconSource
    property alias infoIconSize: infoIcon.size
    property string toolTipText: ""

    property string value: ""

    property string placeholderText: ""
    property bool readOnly: false

    property int fieldWidth: 280
    property int fieldHeight: 36
    property int radius: 8

    signal valueEdited(string value)
    signal accepted(string value)
    signal editingFinished(string value)

    implicitWidth: labelWidth + fieldWidth
                   + (infoText.length > 0 ? infoIconSize + 8 : 0)
                   + 20
    implicitHeight: fieldHeight

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Label {
            visible: root.label.length > 0
            text: root.label
            font.pixelSize: SL.Theme.typography.fontSizeMd
            color: SL.Theme.colors.textPrimary
            opacity: root.enabled ? 1.0 : 0.6

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

            text: root.value

            onTextEdited: {
                root.valueEdited(text)
            }

            onAccepted: {
                root.accepted(text)
            }

            onEditingFinished: {
                root.editingFinished(text)
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
                opacity: root.enabled ? 1.0 : 0.6
            }

            font.pixelSize: SL.Theme.typography.fontSizeMd
            color: root.enabled
                   ? SL.Theme.colors.textPrimary
                   : SL.Theme.colors.textDisabled
            leftPadding: 12
            rightPadding: 12
            verticalAlignment: Text.AlignVCenter

            SL.StyledToolTip {
                visible: field.hovered && root.toolTipText.length > 0
                text: root.toolTipText
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
