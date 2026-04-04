import QtQuick
import QtQuick.Controls
import ScanLab as SL

Rectangle {
    id: root

    property bool active: false

    radius: 8
    color: SL.Theme.colors.windowBackground
    border.width: 1
    border.color: SL.Theme.colors.border
    clip: true

    Button {
        text: "Start A-Scan"
        //onClicked: aScanView.start()
    }

    SL.AScanView {
      id: aScanView

      anchors.fill: parent
      anchors.margins: 8
      sampleCount: 512
  //      minY: -1.0
  //      maxY: 1.0
      active: root.active
      device: backend ? backend.device : null
    }
}
