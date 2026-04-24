import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

    property bool active: false
    property bool settingsPanelOpen: false

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

    ToolButton {
        id: settingsButton

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 8

        width: 36
        height: 36

        checkable: true
        checked: root.settingsPanelOpen

        icon.source: "qrc:/icons/cog.svg"
        icon.width: 22
        icon.height: 22

        background: Rectangle {
            radius: 6
            color: settingsButton.checked
                   ? SL.Theme.colors.primary
                   : SL.Theme.colors.windowBackground
            border.width: 1
            border.color: SL.Theme.colors.border
        }

        onClicked: root.settingsPanelOpen = !root.settingsPanelOpen
    }

    Rectangle {
        id: settingsPanel

        width: 320
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // 👇 позиция: либо на месте, либо за экраном
        x: root.settingsPanelOpen ? parent.width - width : parent.width

        color: SL.Theme.colors.windowBackground
        z: 5

        Behavior on x {
            NumberAnimation {
                duration: 200
                easing.type: Easing.OutCubic
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 1
            color: SL.Theme.colors.border
        }

        // placeholder
        Label {
            anchors.centerIn: parent
            text: qsTr("Settings panel")
            color: SL.Theme.colors.textSecondary
            opacity: 0.6
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