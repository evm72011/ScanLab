pragma Singleton
import QtQuick
import ScanLab 1.0 as SL

QtObject {
    enum Mode { Dark, Light }
    property int mode: Theme.Dark

    readonly property ColorTokens colors: (mode === Theme.Dark) ? SL.ColorTokensDark : SL.ColorTokensLight
}
