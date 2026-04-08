import QtQuick
import QtQuick.Controls
import ScanLab as SL

ApplicationWindow {
    width: 1200
    height: 800
    visible: true
    color: SL.Theme.colors.loadBackground
    title: "ScanLab"

    palette.window: SL.Theme.colors.windowBackground

    Component {
        id: mainPageComponent
        SL.MainPage {}
    }

    StackView {
        id: contentFrame
        anchors.fill: parent
        initialItem: SL.LoadPage {}

        Component {
            id: fadeComponent
            Transition {
                property real fromOpacity: 0
                property real toOpacity: 1
                property int duration: 200

                NumberAnimation {
                    property: "opacity"
                    from: fromOpacity
                    to: toOpacity
                    duration: duration
                }
            }
        }

        function makeFade(fromOpacity, toOpacity, duration) {
            return fadeComponent.createObject(contentFrame, {
                fromOpacity,
                toOpacity,
                duration
            })
        }

        Component.onCompleted: {
            const fadeIn  = makeFade(0, 1, 300)
            const fadeOut = makeFade(1, 0, 150)

            pushEnter    = fadeIn
            popEnter     = fadeIn
            replaceEnter = fadeIn

            pushExit     = fadeOut
            popExit      = fadeOut
            replaceExit  = fadeOut
        }
    }

    Timer {
        id: loadDelayTimer
        interval: 1000
        running: false
        repeat: false
        onTriggered: {
            contentFrame.replace(mainPageComponent)
        }
    }

    Component.onCompleted: {
        loadDelayTimer.start()
    }
}
