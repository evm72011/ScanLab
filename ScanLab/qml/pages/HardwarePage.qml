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

        SL.DropDown {
            Layout.preferredWidth: 250
            Layout.fillWidth: false
            model: ["foo", "bar", "baz"]
            onActivated: console.log("Selected:", currentText)
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
