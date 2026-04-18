import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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
        facade: backend?.ascanFacade ?? null

        lineColor: SL.Theme.colors.ascanLine
        gridColor: SL.Theme.colors.ascanGrid
        markerColor: SL.Theme.colors.ascanMarker
        axisTextColor: SL.Theme.colors.textSecondary
        backgroundColor: SL.Theme.colors.windowBackground
    }

    onActiveChanged: {
        if (!backend || !backend.ascanFacade)
            return

        if (active)
            backend.ascanFacade.start()
        else
            backend.ascanFacade.stop()
    }
}
