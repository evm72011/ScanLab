import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ScanLab 1.0 as SL

Item {
    id: root

    property var model: []
    property int currentIndex: 0
    readonly property string currentText:
        (Array.isArray(model) && model.length > 0
         && currentIndex >= 0 && currentIndex < model.length)
            ? model[currentIndex]
            : ""

    signal activated(int index)

    implicitWidth: 280
    implicitHeight: 36

    property int radius: 8
    property int rowHeight: 36
    property int maxPopupHeight: 240

    Rectangle {
        id: field
        anchors.fill: parent
        radius: root.radius
        color: SL.Theme.colors.controlBackground
        border.color: SL.Theme.colors.border
        border.width: 1
    }

    Text {
        id: valueText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.right: indicator.left
        anchors.rightMargin: 8
        text: root.currentText
        color: SL.Theme.colors.textPrimary
        elide: Text.ElideRight
    }

    // маленькая стрелка (можешь заменить на svg)
    Text {
        id: indicator
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 12
        text: "\u25BE" // ▾
        color: SL.Theme.colors.textPrimary
        opacity: 0.9
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: popup.open()
        onEntered: field.border.width = 1
        onExited: field.border.width = 1
    }

    Popup {
        id: popup
        x: 0
        y: root.height + 6
        width: root.width

        padding: 6
        modal: false
        focus: true
        closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

        implicitHeight: Math.min(list.contentHeight + padding * 2, root.maxPopupHeight)

        background: Rectangle {
            radius: root.radius
            color: SL.Theme.colors.controlBackground
            border.color: SL.Theme.colors.border
            border.width: 1
        }

        contentItem: ListView {
            id: list
            clip: true
            model: root.model
            currentIndex: root.currentIndex
            implicitHeight: contentHeight

            ScrollBar.vertical: ScrollBar { }

            delegate: Item {
                id: row
                width: ListView.view.width
                height: root.rowHeight

                Rectangle {
                    anchors.fill: parent
                    radius: 6
                    color: (index === root.currentIndex)
                           ? SL.Theme.colors.controlChecked
                           : (ma.containsMouse ? SL.Theme.colors.controlHovered : "transparent")
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: modelData
                    color: SL.Theme.colors.textPrimary
                    elide: Text.ElideRight
                }

                MouseArea {
                    id: ma
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        root.currentIndex = index
                        root.activated(index)
                        popup.close()
                    }
                }
            }
        }
    }
}
