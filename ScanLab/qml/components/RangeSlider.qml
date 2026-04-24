import QtQuick
import QtQuick.Controls

Item {
    id: root

    width: 300
    height: 40

    property real leftValue: 0.1
    property real rightValue: 0.1

    function clamp() {
        if (leftValue + rightValue > 1) {
            if (leftDragArea.drag.active)
                rightValue = 1 - leftValue
            else
                leftValue = 1 - rightValue
        }
    }

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: 6
        radius: 3
        color: "#333"
    }

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        height: 6

        x: leftHandle.x + leftHandle.width / 2
        width: rightHandle.x - x + rightHandle.width / 2

        radius: 3
        color: "#66aaff"
    }

    Rectangle {
        id: leftHandle

        width: 14
        height: 14
        radius: 7
        color: "white"

        x: root.leftValue * (root.width - width)
        y: parent.height / 2 - height / 2
        z: 2

        MouseArea {
            id: leftDragArea

            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: rightHandle.x

            onPositionChanged: {
                root.leftValue = parent.x / (root.width - parent.width)
                root.clamp()
            }
        }
    }

    Rectangle {
        id: rightHandle

        width: 14
        height: 14
        radius: 7
        color: "white"

        x: (1 - root.rightValue) * (root.width - width)
        y: parent.height / 2 - height / 2
        z: 2

        MouseArea {
            id: rightDragArea

            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAxis
            drag.minimumX: leftHandle.x
            drag.maximumX: root.width - parent.width

            onPositionChanged: {
                var pos = parent.x / (root.width - parent.width)
                root.rightValue = 1 - pos
                root.clamp()
            }
        }
    }
}