set(QML_SINGLETONS
    themes/Theme.qml
    themes/palette/Palette.qml
    themes/tokens/ColorTokensDark.qml
    themes/tokens/ColorTokensLight.qml
    themes/tokens/TypographyTokens.qml
)

set_source_files_properties(
    ${QML_SINGLETONS}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

set(QML_MODULE_FILES
    components/Button.qml
    components/DropDown.qml
    components/IconTabButton.qml
    components/InfoIcon.qml
    components/StatusBar.qml
    components/StatusChip.qml
    components/TabButton.qml
    components/TemperatureStatusChip.qml
    components/TextField.qml

    dialogs/MessageDialog.qml

    pages/HardwarePage.qml
    pages/LoadPage.qml
    pages/MainPage.qml
    pages/ScanPage.qml
    pages/ScanAPage.qml
    pages/ScanBPage.qml
    pages/ScanCPage.qml
    pages/SettingsPage.qml

    Main.qml
    themes/tokens/ColorTokens.qml
)

qt_target_qml_sources(${APP_NAME}
    QML_FILES
        ${QML_SINGLETONS}
        ${QML_MODULE_FILES}
)
