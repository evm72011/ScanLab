import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    Rectangle {
        anchors.fill: parent
        color: SL.Theme.colors.windowBackground

        /*
        ComboBox {
            id: combo
            Layout.fillWidth: true
            model: ["Foo", "Bar", "Baz"]

            onCurrentTextChanged: {
                console.log("Selected:", currentText)
            }
        }
*/

        Label {
            anchors.centerIn: parent
            text: qsTr("Hardware")
            color: SL.Theme.colors.textPrimary
        }
    }
}
