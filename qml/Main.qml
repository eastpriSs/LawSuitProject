import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 850
    height: 750
    visible: true
    title: qsTr("Lawsuit Pro")
    color: StyleManager.background

    ScrollView {
        id: scrollView
        anchors.fill: parent
        contentWidth: availableWidth
        clip: true
        padding: 60

        RowLayout {
            anchors.fill: parent
            spacing: StyleManager.spacingLarge

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: scrollView.availableWidth * 3/4
                spacing: StyleManager.spacingMedium
                anchors.leftMargin: 35
                anchors.rightMargin: 35
                anchors.topMargin: 30
                anchors.bottomMargin: 30

                Text {
                    text: qsTr("ProfitExpert")
                    font.pixelSize: StyleManager.fontSizeLarge
                    font.weight: Font.DemiBold
                    color: StyleManager.textColor
                    Layout.fillWidth: true
                    Layout.bottomMargin: 5
                }

                CustomGroupBox {
                    title: "Основная информация"
                    Layout.fillWidth: true

                    GridLayout {
                        anchors.fill: parent
                        columns: 2
                        rowSpacing: 14
                        columnSpacing: 18

                        Text { text: "Дело:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: StyleManager.spacingSmall
                            TextField { id: caseNameInput; placeholderText: "Название или суть дела"; Layout.fillWidth: true }
                            TextField { id: caseIDInput; placeholderText: "Рег. номер"; Layout.preferredWidth: 180 }
                        }

                        Text { text: "Дата получения:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
                        Button {
                            id: dateButton
                            text: "Выбрать дату"
                            Layout.fillWidth: true
                            onClicked: mainDatePicker.open()
                        }

                        Text { text: "Судья:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: StyleManager.spacingSmall
                            TextField { id: lawyerNameInput; placeholderText: "ФИО судьи"; Layout.fillWidth: true }
                            Text { text: "Тел.:"; color: StyleManager.secondaryText }
                            TextField { id: lawyerNumberInput; inputMask: "+7 (000) 000-00-00;_"; Layout.preferredWidth: StyleManager.phoneWidth }
                        }

                        Text { text: "Суд:"; color: StyleManager.secondaryText; Layout.preferredWidth: StyleManager.labelWidth; horizontalAlignment: Text.AlignRight; verticalAlignment: Text.AlignVCenter }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: StyleManager.spacingSmall
                            ComboBox {
                                model: ["Арбитражный", "Мировой", "Районный"]
                                Layout.fillWidth: true
                            }
                            Text { text: "Адрес:"; color: StyleManager.secondaryText }
                            ComboBox {
                                model: ["ул. Ленина, 1", "пр. Мира, 45"]
                                Layout.preferredWidth: StyleManager.phoneWidth
                            }
                        }
                    }
                }
                PlaintiffGroupBox { Layout.fillWidth: true }
                DefendantGroupBox { Layout.fillWidth: true }
                ExpertiseGroupBox { id: expertiseBox; Layout.fillWidth: true;  }

                DatePickerPopup {
                    id: mainDatePicker
                    onDateSelected: (dateText) => { dateButton.text = dateText }
                }
            }

            ColumnLayout {
                id: rightColumn
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: scrollView.availableWidth * 1/4
                spacing: StyleManager.spacingTiny

                Text {
                    text: qsTr("Шаблоны")
                    font.pixelSize: StyleManager.fontSizeTitle
                    font.weight: Font.DemiBold
                    color: StyleManager.textColor
                    Layout.fillWidth: true
                    Layout.bottomMargin: 5
                }

                FileListView {
                    id: filesListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: FileModel
                }

                ActionButtons {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 3 * StyleManager.buttonHeight + 2 * StyleManager.spacingTiny
                }
            }
        }
    }
}
