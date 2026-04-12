import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

    property int connectionState: backend?.connectionFacade?.connectionState ??
                                  SL.ConnectionState.Disconnected

    readonly property bool connected:
        connectionState === SL.ConnectionState.Connected

    readonly property var temperatureFacade: backend?.temperatureFacade ?? null

    readonly property bool maxTemperatureUnavailable: temperatureFacade?.maxTemperatureUnavailable ?? true
    readonly property string maxTemperatureErrorCode: temperatureFacade?.maxTemperatureErrorCode ?? ""
    readonly property int maxTemperature: temperatureFacade?.maxTemperature ?? 0

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
            return "#ff6b6b"   // всегда красный для Err
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
        if (!temperatureFacade) {
            return
        }

        if (connected) {
            temperatureFacade.startMaxTemperaturePolling()
        } else {
            temperatureFacade.stopMaxTemperaturePolling()
        }
    }

    HoverHandler {
        id: hoverHandler
    }

    StyledToolTip {
        id: errorTip
        text: root.maxTemperatureUnavailable
              ? qsTr("Unable to read humidity!\nErrorCode: %1").arg(root.maxTemperatureErrorCode)
              : qsTr("Humidity")
        visible: hoverHandler.hovered
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
            source: "qrc:/icons/humidity.svg"
            width: 16
            height: 16
            fillMode: Image.PreserveAspectFit
            smooth: true
            opacity: root.connected && !root.maxTemperatureUnavailable ? 1.0 : 0.65
        }

        Text {
            text: {
                if (!root.connected) {
                    return qsTr("Humidity: n/a")
                }

                if (root.maxTemperatureUnavailable) {
                    return qsTr("Humidity: Err")
                }

                return qsTr("%1 %").arg(root.maxTemperature)
            }

            color: root.tempColor
            font.pixelSize: 12
            font.weight: !root.maxTemperatureUnavailable ? Font.Medium : Font.Normal
            verticalAlignment: Text.AlignVCenter
        }
    }

    Component.onCompleted: updatePolling()
    onConnectedChanged: updatePolling()
    onTemperatureFacadeChanged: updatePolling() /// ?????

    Component.onDestruction: {
        temperatureFacade?.stopMaxTemperaturePolling()
    }
}