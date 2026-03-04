pragma Singleton
import QtQuick
import ScanLab 1.0 as SL

ColorTokens {
    property var p: SL.Palette

    windowBackground: p.slate300

    textPrimary: p.gray900
    textSecondary: p.gray800
}
