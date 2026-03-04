import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    Rectangle {
        anchors.fill: parent
        color: SL.Theme.colors.windowBackground
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        ComboBox {
            id: combo
            Layout.preferredWidth: 250
            Layout.fillWidth: false

            model: ["Foo", "Bar", "Baz"]

            background: Rectangle {
                radius: 6
                color: SL.Theme.colors.windowBackground
                border.color: SL.Theme.colors.border
                border.width: 1
            }

            contentItem: Text {
                text: combo.displayText
             ///   color: SL.Theme.colors.textPrimary
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                leftPadding: 10
                rightPadding: 28
            }

            popup.background: Rectangle {
                radius: 6
                color: SL.Theme.colors.windowBackground
                border.color: SL.Theme.colors.border
                border.width: 1
            }

            onCurrentTextChanged: console.log("Selected:", currentText)
        }

        Item { Layout.fillHeight: true }

        Label {
            text: qsTr("Hardware")
            color: SL.Theme.colors.textPrimary
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }
}
