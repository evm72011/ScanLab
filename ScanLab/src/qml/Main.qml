import QtQuick
import QtQuick.Controls
import ScanLab as SL

Window {
    width: 640
    height: 480
    visible: true
    color: "#2C3E50"
    title: qsTr("ScanLab")

    Component {
        id: mainPageComponent
        SL.MainPage {}
    }

    StackView {
        id: contentFrame
        anchors.fill: parent
        initialItem: SL.LoadPage {}
    }

    Component.onCompleted: contentFrame.replace(mainPageComponent)

}
