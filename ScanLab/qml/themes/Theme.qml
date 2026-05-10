pragma Singleton
import QtQuick
import ScanLab as SL

QtObject {
    enum Mode { Dark, Light }
    property int mode: Theme.Dark

    readonly property ColorTokens colors: (mode === Theme.Dark) ? SL.ColorTokensDark : SL.ColorTokensLight
    readonly property TypographyTokens typography: SL.TypographyTokens
    readonly property LayoutTokens layout: SL.LayoutTokens
}
