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

        // 👇 border слева
        Rectangle {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            color: SL.Theme.colors.border
        }

        // 👇 rail (иконки)
        Rectangle {
            Layout.preferredWidth: root.collapsedWidth - 1
            Layout.fillHeight: true
            color: SL.Theme.colors.windowBackground

            ColumnLayout {
                anchors.fill: parent
                spacing: 8

                Item { Layout.preferredHeight: 12 }

                // ⚙
                ToolButton {
                    id: cogTab

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 30

                    checkable: true
                    checked: root.expanded

                    icon.source: "qrc:/icons/cog.svg"

                    background: Rectangle {
                        radius: 6
                        color: cogTab.checked
                               ? SL.Theme.colors.primary
                               : cogTab.hovered
                                 ? Qt.rgba(1,1,1,0.08)
                                 : "transparent"
                    }

                    onClicked: root.expanded = true
                }

                // >>
                ToolButton {
                    id: collapseButton

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 30

                    visible: root.expanded

                    icon.source: "qrc:/icons/double-right.svg"

                    background: Rectangle {
                        radius: 6
                        color: collapseButton.hovered
                               ? Qt.rgba(1,1,1,0.08)
                               : "transparent"
                    }

                    onClicked: root.expanded = false
                }

                Item { Layout.fillHeight: true }
                Item { Layout.preferredHeight: 12 }
            }
        }

        // 👇 content area
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: root.expanded
            clip: true

            Label {
                anchors.centerIn: parent
                text: qsTr("A-scan settings")
                color: SL.Theme.colors.textSecondary
                opacity: 0.6
            }
        }
    }
}