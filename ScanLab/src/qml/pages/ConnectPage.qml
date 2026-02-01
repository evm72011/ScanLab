import QtQuick
import QtQuick.Controls

Item {
    width:  SwipeView.view ? SwipeView.view.width  : 0
    height: SwipeView.view ? SwipeView.view.height : 0

    Rectangle {
        anchors.fill: parent
        color: "#2C3E50"

        Button {
            width: 200
            height: 50
            anchors.centerIn: parent
            onClicked: backend.connectDevice("192.168.1.11")

            Text {
                text: "Connect..."
                color: "black"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                font.pointSize: 10
                font.bold: true
            }
        }
    }
}
