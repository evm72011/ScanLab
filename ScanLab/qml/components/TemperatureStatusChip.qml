import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

    property int connectionState: backend?.connection?.connectionState ??
                                  SL.ConnectionState.Disconnected

    readonly property bool connected:
        connectionState === SL.ConnectionState2.Connected

    readonly property var healthFacade: backend?.healthFacade ?? null

    readonly property bool maxTemperatureUnavailable: healthFacade?.maxTemperatureUnavailable ?? true
    readonly property string maxTemperatureErrorCode: healthFacade?.maxTemperatureErrorCode ?? ""
    readonly property int maxTemperature: healthFacade?.maxTemperature ?? 0

    height: 30
    radius: 4
    color: "transparent"
    implicitWidth: row.implicitWidth + 12

    readonly property color textColor: SL.Theme.colors.textPrimary

    readonly property color tempColor: {
        if (!connected) {
            return Qt.rgba(1, 1, 1, 0.55)
        }

        if (maxTemperatureUnavailable) {
            return "#ff6b6b"   // 🔴 всегда красный для Err
        }

        if (maxTemperature >= 50) {
            return "#ff6b6b"
        }

        if (maxTemperature >= 40) {
            return "#ffb347"
        }

        return "#9ad27a"
    }

    function updatePolling() {
        if (!healthFacade) {
            return
        }

        if (connected) {
            healthFacade.startMaxTemperaturePolling()
        } else {
            healthFacade.stopMaxTemperaturePolling()
        }
    }

    HoverHandler {
        id: hoverHandler
    }

    StyledToolTip {
        id: errorTip
        text: qsTr("Unable to read temperature!\nErrorCode: %1")
                .arg(root.maxTemperatureErrorCode)
        visible: hoverHandler.hovered && root.maxTemperatureUnavailable && root.connected
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
            opacity: root.connected && !root.maxTemperatureUnavailable ? 1.0 : 0.65
        }

        Text {
            text: {
                if (!root.connected) {
                    return qsTr("Temperature: n/a")
                }

                if (root.maxTemperatureUnavailable) {
                    return qsTr("Temperature: Err")
                }

                return qsTr("Temp: %1 °C").arg(root.maxTemperature)
            }

            color: root.tempColor
            font.pixelSize: 12
            font.weight: !root.maxTemperatureUnavailable ? Font.Medium : Font.Normal
            verticalAlignment: Text.AlignVCenter
        }
    }

    Component.onCompleted: updatePolling()
    onConnectedChanged: updatePolling()
    onHealthFacadeChanged: updatePolling()

    Component.onDestruction: {
        healthFacade?.stopPolling()
    }
}