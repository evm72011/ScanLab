pragma Singleton
import QtQuick
import ScanLab 1.0 as SL

ColorTokens {
    property var p: SL.Palette

    loadBackground: p.slate700

    windowBackground: p.gray800

    toolbarBackground: p.gray850
    toolbarIcon: p.blue400
    toolbarButtonDown: p.gray600
    toolbarButtonChecked: p.cyan1200
    toolbarButtonHovered: p.gray700
    toolbarNormalText: p.gray100
    toolbarActiveText: p.gray000

    statusbarBackground: p.gray850

    border: p.gray700

    textPrimary: p.gray200
    textSecondary: p.gray300
}
