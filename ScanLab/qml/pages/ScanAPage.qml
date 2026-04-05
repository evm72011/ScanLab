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

    SL.AScanView {
      id: aScanView

      anchors.fill: parent
      anchors.margins: 8
      sampleCount: 512

      soundVelocity: 5900     // сталь
      timeRangeUs: 29       // ← ВАЖНО: это нужно подобрать/взять из прибора
      timeStartUs: 0.0

      active: root.active
      device: backend ? backend.device : null
    }
}
