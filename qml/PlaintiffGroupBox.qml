import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

CustomGroupBox {
    title: "Истец"

    readonly property bool isHighlightNeeded: Highlight.activeFields.indexOf(title) !== -1

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: 14
        columnSpacing: 18

        // ФИО
        Text {
            text: "ФИО / Наименование:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        TextField {
            id: plaintiffNameField
            placeholderText: "Иванов Иван Иванович"
            Layout.fillWidth: true
        }

        // Адрес
        Text {
            text: "Адрес:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        TextField {
            id: plaintiffAddressField
            placeholderText: "Город, улица, дом, квартира"
            Layout.fillWidth: true
        }

        // Телефон
        Text {
            text: "Телефон:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        TextField {
            id: plaintiffPhoneField
            inputMask: "+7 (000) 000-00-00;_"
            placeholderText: "+7 (***) *******-**"
            Layout.fillWidth: true
        }

        // Представитель
        Text {
            text: "Представитель:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        TextField {
            id: plaintiffRepField
            placeholderText: "ФИО представителя по доверенности"
            Layout.fillWidth: true
        }
    }
}
