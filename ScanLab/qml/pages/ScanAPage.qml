import QtQuick
import ScanLab as SL

Rectangle {
    id: root

    property bool active: false

    radius: 8
    color: SL.Theme.colors.windowBackground
    border.width: 1
    border.color: SL.Theme.colors.border
    clip: true

    SL.AScanView {
        anchors.fill: parent
        anchors.margins: 8
        sampleCount: 512
  //      minY: -1.0
  //      maxY: 1.0
        active: true //root.active
        device: backend ? backend.device : null
    }
}
