import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

    readonly property int connectionState: backend?.connectionFacade?.connectionState ??
                                  SL.ConnectionState.Disconnected
    readonly property bool connected: connectionState === SL.ConnectionState.Connected

    property bool expanded: false
    property int collapsedWidth: 40
    property int panelWidth: 280
    property int minWidth: 200
    property int maxWidth: 600

    implicitWidth: expanded ? panelWidth : collapsedWidth
    color: SL.Theme.colors.windowBackground
    clip: true

    Behavior on implicitWidth {
        NumberAnimation {
            duration: 180
            easing.type: Easing.OutCubic
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: leftBorder
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            color: SL.Theme.colors.border
            visible: !root.expanded
        }

        Rectangle {
            Layout.preferredWidth: root.collapsedWidth - 1
            Layout.fillHeight: true
            color: SL.Theme.colors.windowBackground

            ColumnLayout {
                anchors.fill: parent

                Item { Layout.preferredHeight: 6 }

                SL.RailIconButton {
                    Layout.alignment: Qt.AlignHCenter

                    iconSource: "qrc:/icons/cog.svg"
                    active: root.expanded

                    onActivated: root.expanded = true
                }

                Item { Layout.fillHeight: true }

                SL.RailIconButton {
                    Layout.alignment: Qt.AlignHCenter

                    visible: root.expanded
                    iconSource: "qrc:/icons/double-right.svg"
                    iconSize: 10

                    onActivated: root.expanded = false
                }
                Item { Layout.preferredHeight: 6 }
            }
        }

        Rectangle {
            id: rightBorder
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            color: SL.Theme.colors.border
            visible: root.expanded
        }

        Item {
            id: contentArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: root.expanded
            clip: true
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                SL.DropDown {
                    label: qsTr("Cycle")
                    labelWidth: 40
                    fieldWidth: 75
                    infoText: qsTr("Select the active cycle")

                    model: backend?.acquisitionConfigurationFacade.cycles ?? []
                    currentValue: backend?.acquisitionConfigurationFacade.cycle ?? 0
                    enabled: root.connected

                    onActivated: function(value) {
                        backend.acquisitionConfigurationFacade.setCycle(value)
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }
}
