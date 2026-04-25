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

    RowLayout {
        anchors.fill: parent
        spacing: 0

        SL.AScanView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            facade: backend?.ascanFacade ?? null

            lineColor: SL.Theme.colors.ascanLine
            gridColor: SL.Theme.colors.ascanGrid
            markerColor: SL.Theme.colors.ascanMarker
            axisTextColor: SL.Theme.colors.textSecondary
            backgroundColor: SL.Theme.colors.windowBackground
        }

        SL.HorizontalResizeHandle {
            visible: ascanSettings.expanded

            coordinateItem: root
            targetWidth: ascanSettings.panelWidth
            minWidth: ascanSettings.minWidth
            maxWidth: ascanSettings.maxWidth

            onWidthChangedByUser: function(width) {
                ascanSettings.panelWidth = width
            }
        }

        SL.AScanSettingsPage {
            id: ascanSettings
            Layout.preferredWidth: implicitWidth
            Layout.fillHeight: true
        }
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