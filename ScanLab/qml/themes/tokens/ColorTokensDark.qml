pragma Singleton
import QtQuick
import ScanLab 1.0 as SL

ColorTokens {
    property var p: SL.Palette

    loadBackground: p.slate700

    windowBackground: p.gray800

    controlBackground: p.gray800
    controlDown: p.gray600
    controlChecked: p.cyan1200
    controlHovered: p.gray700

    controlNormalText: p.gray100
    controlActiveText: p.gray000

    toolbarIcon: p.blue400


    statusbarBackground: p.gray850

    border: p.gray700

    textPrimary: p.gray200
    textSecondary: p.gray300
}
