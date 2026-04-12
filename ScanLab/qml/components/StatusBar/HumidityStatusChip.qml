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

    readonly property var humidityFacade: backend?.humidityFacade ?? null

    readonly property bool maxHumidityUnavailable: humidityFacade?.maxHumidityUnavailable ?? true
    readonly property string maxHumidityErrorCode: humidityFacade?.maxHumidityErrorCode ?? ""
    readonly property int maxHumidity: humidityFacade?.maxHumidity ?? 0

    height: 30
    radius: 4
    color: "transparent"
    implicitWidth: row.implicitWidth + 12

    readonly property color textColor: SL.Theme.colors.textPrimary

    readonly property color tempColor: {
        if (maxHumidity >= 75 || maxHumidityUnavailable) {
            return  SL.Theme.colors.textError // "#ff6b6b"
        }

        if (maxHumidity >= 60) {
            return SL.Theme.colors.textWarning // "#ffb347"
        }

        return "#9ad27a"
    }

    function updatePolling() {
        if (!humidityFacade) {
            return
        }

        if (connected) {
            humidityFacade.startMaxHumidityPolling()
        } else {
            humidityFacade.stopMaxHumidityPolling()
        }
    }

    HoverHandler {
        id: hoverHandler
    }

    StyledToolTip {
        text: root.maxHumidityUnavailable
              ? qsTr("Unable to read humidity!\nErrorCode: %1").arg(root.maxHumidityErrorCode)
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
            opacity: root.connected && !root.maxHumidityUnavailable ? 1.0 : 0.65
        }

        Text {
            text: {
                if (!root.connected) {
                    return qsTr("Humidity: n/a")
                }

                if (root.maxHumidityUnavailable) {
                    return qsTr("Humidity: Err")
                }

                return qsTr("%1 %").arg(root.maxHumidity)
            }

            color: root.tempColor
            font.pixelSize: 12
            font.weight: !root.maxHumidityUnavailable ? Font.Medium : Font.Normal
            verticalAlignment: Text.AlignVCenter
        }
    }

    Component.onCompleted: updatePolling()
    onConnectedChanged: updatePolling()
    onHumidityFacadeChanged: updatePolling() /// ?????

    Component.onDestruction: {
        humidityFacade?.stopMaxHumidityPolling()
    }
}