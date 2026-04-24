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

        Rectangle {
            id: ascanSettingsResizeHandle

            Layout.preferredWidth: ascanSettings.expanded ? 4 : 0
            Layout.fillHeight: true
            visible: ascanSettings.expanded

            color: resizeArea.containsMouse || resizeArea.pressed
                   ? Qt.rgba(1, 1, 1, 0.18)
                   : Qt.rgba(1, 1, 1, 0.06)

            MouseArea {
                id: resizeArea

                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.SizeHorCursor

                property real startRootX: 0
                property int startWidth: 0

                onPressed: function(mouse) {
                    startRootX = ascanSettingsResizeHandle.mapToItem(root, mouse.x, mouse.y).x
                    startWidth = ascanSettings.panelWidth
                }

                onPositionChanged: function(mouse) {
                    if (!pressed)
                        return

                    var currentRootX = ascanSettingsResizeHandle.mapToItem(root, mouse.x, mouse.y).x
                    var dx = currentRootX - startRootX

                    ascanSettings.panelWidth = Math.max(
                        ascanSettings.minWidth,
                        Math.min(ascanSettings.maxWidth, startWidth - dx)
                    )
                }
            }
        }

        SL.AScanSettings {
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