import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    property Item targetItem: null
    property Item coordinateItem: null

    property int targetWidth: 0
    property int minWidth: 200
    property int maxWidth: 600

    signal widthChangedByUser(int width)

    Layout.preferredWidth: visible ? 4 : 0
    Layout.fillHeight: true

    color: resizeArea.containsMouse || resizeArea.pressed
           ? Qt.rgba(1, 1, 1, 0.18)
           : Qt.rgba(1, 1, 1, 0.06)

    MouseArea {
        id: resizeArea

        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.SizeHorCursor

        property real startX: 0
        property int startWidth: 0

        onPressed: function(mouse) {
            startX = root.mapToItem(root.coordinateItem, mouse.x, mouse.y).x
            startWidth = root.targetWidth
        }

        onPositionChanged: function(mouse) {
            if (!pressed || !root.coordinateItem)
                return

            var currentX = root.mapToItem(root.coordinateItem, mouse.x, mouse.y).x
            var dx = currentX - startX

            var newWidth = Math.max(
                root.minWidth,
                Math.min(root.maxWidth, startWidth - dx)
            )

            root.targetWidth = newWidth
            root.widthChangedByUser(newWidth)
        }
    }
}
