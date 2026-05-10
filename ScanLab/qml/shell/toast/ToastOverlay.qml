import QtQuick
import QtQuick.Controls
import ScanLab as SL

Item {
    id: root

    anchors.fill: parent
    z: 9999

    ListModel {
        id: toastModel
    }

    Connections {
        target: backend?.toastFacade ?? null

        function onToastRequested(titleText, bodyText, iconSource, durationMs) {
            toastModel.append({
                titleText,
                bodyText,
                iconSource,
                durationMs
            })
        }
    }

    Column {
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.rightMargin: 10
        anchors.bottomMargin: SL.Theme.layout.statusBarHeight + 10

        spacing: 10

        Repeater {
            model: toastModel

            SL.Toast {
                titleText: model.titleText
                bodyText: model.bodyText
                iconSource: model.iconSource
                durationMs: model.durationMs

                onExpired: {
                    toastModel.remove(index)
                }
            }
        }
    }
}