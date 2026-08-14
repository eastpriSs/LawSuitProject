import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    font.weight: Font.DemiBold
    font.family: "sans-serif"
    font.pixelSize: StyleManager.fontSizeGroup
    padding: StyleManager.paddingGroup
    topPadding: StyleManager.topPaddingGroup

    background: Rectangle {
        color: StyleManager.background
        border.color: StyleManager.borderColor
        border.width: 1
        radius: 4
    }
}
