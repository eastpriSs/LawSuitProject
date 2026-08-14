import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

CustomGroupBox {
    title: "Экспертиза"

    property alias expertiseType: typeField.text
    property alias expertiseSubject: subjectField.text
    property alias expertModel: expertCombo.model
    property alias expertCurrentIndex: expertCombo.currentIndex
    property alias travelCost: travelField.text
    property alias totalCost: totalField.text
    property alias dateButtonText: expDateButton.text

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: 14
        columnSpacing: 18

        Text { text: "Вид экспертизы:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField { id: typeField; placeholderText: "Например: Строительно-техническая"; Layout.fillWidth: true }

        Text { text: "Предмет:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField { id: subjectField; placeholderText: "Объект исследования"; Layout.fillWidth: true }

        Text { text: "Эксперт:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        ComboBox {
            id: expertCombo
            model: ["Не назначен", "Сидоров С.С.", "ООО \"ГлавЭкспертиза\"", "АНО \"Судэксперт\""]
            Layout.fillWidth: true
        }

        Text { text: "Срок исполнения:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        Button {
            id: expDateButton
            text: "Выбрать дату"
            Layout.fillWidth: true
            onClicked: expDatePicker.open()
        }

        Text { text: "Стоимость выезда (₽):"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField {
            id: travelField
            placeholderText: "0.00"
            Layout.fillWidth: true
            validator: RegularExpressionValidator { regularExpression: /^\d+(\.\d{1,2})?$/ }
        }

        Text { text: "Итог (₽):"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField {
            id: totalField
            placeholderText: "0.00"
            Layout.fillWidth: true
            validator: RegularExpressionValidator { regularExpression: /^\d+(\.\d{1,2})?$/ }
        }
    }

    property alias expDatePicker: expDatePicker
    DatePickerPopup {
        id: expDatePicker
        onDateSelected: (dateText) => { expDateButton.text = dateText }
    }
}
