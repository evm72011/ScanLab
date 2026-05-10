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

        function onToastRequested(title, text, iconSource, durationMs) {
            toastModel.append({
                titleText: title,
                bodyText: text,
                iconSource: iconSource,
                durationMs: durationMs
            })
        }
    }

    Column {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 16
        spacing: 8

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