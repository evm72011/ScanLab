import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab as SL

Rectangle {
    id: root

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

        // 👇 content area
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: root.expanded
            clip: true
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Button {
                    text: "Read cycles"

                    onClicked: {
                        backend.acquisitionConfigurationFacade.refresh()
                    }
                }

                Text {
                    text: "Cycles: " + backend.acquisitionConfigurationFacade.cycleCount
                    color: SL.Theme.colors.text
                }

                Connections {
                    target: backend.acquisitionConfigurationFacade

                    function onCycleCountChanged() {
                        console.log("Cycle count:", backend.acquisitionConfigurationFacade.cycleCount)
                    }

                    function onErrorCodeChanged() {
                        console.log("Scan config error:", backend.acquisitionConfigurationFacade.errorCode)
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }
}
