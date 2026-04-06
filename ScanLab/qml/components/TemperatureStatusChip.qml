import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

    readonly property var device: backend?.device ?? null
    readonly property var healthMonitor: backend?.healthMonitor ?? null

    readonly property bool connected:
        device?.connectionState === SL.ConnectionState.Connected

    readonly property int maxTemperature:
        healthMonitor?.maxTemperature ?? -1

    readonly property var temperatures:
        healthMonitor?.temperatures ?? []

    readonly property bool hasTemperature:
        healthMonitor?.hasTemperature ?? false

    height: 30
    radius: 4
    color: "transparent"
    implicitWidth: row.implicitWidth + 12

    readonly property color textColor: SL.Theme.colors.textPrimary

    readonly property color tempColor: {
        if (!hasTemperature) {
            return Qt.rgba(1, 1, 1, 0.55)
        }

        if (maxTemperature >= 50) {
            return "#ff6b6b"
        }

        if (maxTemperature >= 40) {
            return "#ffb347"
        }

        return "#9ad27a"
    }

    HoverHandler {
        id: hoverHandler
    }

    Rectangle {
        anchors.fill: parent
        radius: 4
        color: hoverHandler.hovered ? Qt.rgba(1, 1, 1, 0.05) : "transparent"
    }

    Row {
        id: row
        anchors.verticalCenter: parent.verticalCenter
        x: 6
        spacing: 6

        Image {
            source: "qrc:/icons/temperature-low.svg"
            width: 16
            height: 16
            fillMode: Image.PreserveAspectFit
            smooth: true
            opacity: root.hasTemperature ? 1.0 : 0.65
        }

        Text {
            text: {
                if (!root.connected) {
                    return qsTr("Temperature: n/a")
                }

                if (!root.hasTemperature) {
                    return qsTr("Temperature: --")
                }

                return qsTr("Temp: %1 °C").arg(root.maxTemperature)
            }

            color: root.hasTemperature ? root.tempColor : root.textColor
            font.pixelSize: 12
            font.weight: root.hasTemperature ? Font.Medium : Font.Normal
            verticalAlignment: Text.AlignVCenter
        }
    }

    ToolTip {
        id: tooltip
        visible: hoverHandler.hovered && root.connected && root.temperatures.length > 0
        delay: 300
        timeout: -1

        contentItem: Column {
            spacing: 6

            Text {
                text: qsTr("Temperature sensors")
                color: SL.Theme.colors.textPrimary
                font.pixelSize: 12
                font.weight: Font.DemiBold
            }

            Repeater {
                model: root.temperatures

                delegate: Row {
                    spacing: 10

                    Text {
                        text: qsTr("Board %1").arg(modelData.board)
                        color: SL.Theme.colors.textPrimary
                        font.pixelSize: 12
                    }

                    Text {
                        text: qsTr("Sensor %1").arg(modelData.sensor)
                        color: SL.Theme.colors.textPrimary
                        font.pixelSize: 12
                    }

                    Text {
                        text: qsTr("%1 °C").arg(modelData.valueCelsius)
                        color: SL.Theme.colors.textPrimary
                        font.pixelSize: 12
                        font.weight: Font.Medium
                    }
                }
            }
        }

        background: Rectangle {
            radius: 6
            color: Qt.rgba(0.08, 0.08, 0.08, 0.96)
            border.width: 1
            border.color: Qt.rgba(1, 1, 1, 0.10)
        }

        leftPadding: 10
        rightPadding: 10
        topPadding: 8
        bottomPadding: 8
    }
}