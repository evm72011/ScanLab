pragma Singleton
import QtQuick
import ScanLab as SL

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

    tabChecked: p.gray800
    tabDefault: p.gray650

    statusbarBackground: p.gray850

    border: p.gray700

    textPrimary: p.gray200
    textSecondary: p.gray300
    textDisabled: p.gray500

    textSuccess: p.green300
    textWarning: p.yellow600
    textError: p.red700

    ascanLine: p.sky600
    ascanGrid: p.teal900
    ascanMarker: p.amber500
}
