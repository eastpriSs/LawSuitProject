import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

CustomGroupBox {
    property alias nameText: nameField.text
    property alias addressText: addressField.text
    property alias phoneText: phoneField.text
    property alias repText: repField.text
    property string titleText: ""

    title: titleText

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: 14
        columnSpacing: 18

        Text { text: "ФИО / Наименование:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField { id: nameField; placeholderText: "Иванов Иван Иванович"; Layout.fillWidth: true }

        Text { text: "Адрес:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField { id: addressField; placeholderText: "Город, улица, дом, квартира"; Layout.fillWidth: true }

        Text { text: "Телефон:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField { id: phoneField; inputMask: "+7 (000) 000-00-00;_"; placeholderText: "+7 (***) *******-**"; Layout.fillWidth: true }

        Text { text: "Представитель:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
        TextField { id: repField; placeholderText: "ФИО представителя по доверенности"; Layout.fillWidth: true }
    }
}
