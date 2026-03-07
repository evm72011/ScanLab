pragma Singleton
import QtQuick
import "ErrorTextUtil.js" as ErrorTextUtil

QtObject {
    id: root

    property bool loaded: false

    function init() {
        if (loaded)
            return

        const xhr = new XMLHttpRequest()
        xhr.open("GET", "qrc:/json/errors.json")
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                ErrorTextUtil.load(xhr.responseText)
                loaded = true
            }
        }
        xhr.send()
    }

    function get(category, key) {
        init()
        return ErrorTextUtil.get(category, key)
    }
}
