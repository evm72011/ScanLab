pragma Singleton
import QtQuick
import ScanLab 1.0 as SL

ColorTokens {
    property var p: SL.Palette

    loadBackground:         p.slate700
    windowBackground:       p.gray800
    toolbarBackground:      p.gray850
    statusbarBackground:    p.gray850

    textPrimary:    p.gray200
    textSecondary:  p.gray300
}
