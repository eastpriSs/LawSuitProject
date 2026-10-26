import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

CustomGroupBox {
    title: "Экспертиза"

    signal editTypeClicked()
    signal editExpertClicked()

    readonly property bool isHighlightNeeded: Highlight.activeFields.indexOf(title) !== -1

    property alias expertiseType: typeField.model
    property alias expertModel: expertCombo.model
    property alias expertCurrentIndex: expertCombo.currentIndex
    property alias travelCost: travelField.text
    property alias totalCost: totalField.text
    property alias dateButtonText: expDateButton.text
    property alias expertCurrentText: expertCombo.currentText

    property alias totalCostWords: totalFieldWords.text
    property alias usdCost: usdField.text
    property alias usdCostWords: usdFieldWords.text
    property alias accountNumberText: accountNumber.text
    property alias accountDateButtonText: accountDateButton.text

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: 14
        columnSpacing: 18

        Text {
            text: "Вид экспертизы:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        RowLayout {
            ComboBox {
                id: typeField
                Layout.fillWidth: true
            }
            Button {
                id: editTypeModel
                text: "+"
                onClicked: editTypeClicked()
            }
        }

        Text {
            text: "Эксперт:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        RowLayout {
            ComboBox {
                id: expertCombo
                Layout.fillWidth: true
            }
            Button {
                id: editExpertModel
                text: "+"
                onClicked: editExpertClicked()
            }
        }
        Text {
            text: "Срок исполнения:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        Button {
            id: expDateButton
            text: "Выбрать дату"
            Layout.fillWidth: true
            onClicked: expDatePicker.open()
        }

        Text {
            text: "Стоимость выезда (₽):"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        TextField {
            id: travelField
            placeholderText: "0.00"
            Layout.fillWidth: true
            validator: RegularExpressionValidator { regularExpression: /^\d+(\.\d{1,2})?$/ }
        }

        Text {
            text: "Итог (₽):"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        RowLayout {
            TextField {
                id: totalField
                placeholderText: "0.00"
                Layout.fillWidth: true
                validator: RegularExpressionValidator { regularExpression: /^\d+(\.\d{1,2})?$/ }
            }
            TextField {
                id: totalFieldWords
                Layout.fillWidth: true
                font.italic: true
            }
        }


        Text {
            text: "Сумма на УСД (₽):"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        RowLayout {
            TextField {
                id: usdField
                placeholderText: "0.00"
                Layout.fillWidth: true
                validator: RegularExpressionValidator { regularExpression: /^\d+(\.\d{1,2})?$/ }
            }
            TextField {
                id: usdFieldWords
                Layout.fillWidth: true
                font.italic: true
            }
        }

        Text {
            text: "Номер счета:"
            color: (isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                   ? StyleManager.accentTextColor : StyleManager.secondaryText
            font.weight: Font.Normal
            Layout.preferredWidth: StyleManager.labelWidth
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        RowLayout {
            TextField {
                id: accountNumber
                Layout.fillWidth: true
            }
            Button {
                id: accountDateButton
                text: "Выбрать дату счёта"
                Layout.fillWidth: true
                onClicked: accDatePicker.open()
            }
        }
    }

    property alias expDatePicker: expDatePicker
    DatePickerPopup {
        id: expDatePicker
        onDateSelected: (dateText) => { expDateButton.text = dateText }
    }

    property alias accDatePicker: accDatePicker
    DatePickerPopup {
        id: accDatePicker
        onDateSelected: (dateText) => { accountDateButton.text = dateText }
    }
}
