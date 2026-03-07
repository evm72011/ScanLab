var data = {}

function load(jsonText) {
    data = JSON.parse(jsonText)
}

function get(category, key) {
    if (!data[category])
        return ""

    if (!data[category][key])
        return ""

    return data[category][key]
}
