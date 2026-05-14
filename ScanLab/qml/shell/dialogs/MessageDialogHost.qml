import QtQuick
import QtQuick.Controls
import ScanLab as SL

Item {
    id: root

    anchors.fill: parent
    z: 10000

    Connections {
        target: backend?.shellFacade?.messageFacade ?? null

        function onMessageRequested(title, shortText, detailsText, errorCode, iconSource) {
            messageDialog.dialogTitle = title
            messageDialog.shortText = shortText
            messageDialog.detailsText = detailsText
            messageDialog.errorCode = errorCode
            messageDialog.iconSource = iconSource
            messageDialog.open()
        }
    }

    SL.MessageDialog {
        id: messageDialog
    }
}
