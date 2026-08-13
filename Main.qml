import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 850
    height: 750
    visible: true
    title: qsTr("Lawsuit Pro")
    color: "#f4f6f9"

    ScrollView {
        id: scrollView
        anchors.fill: parent
        contentWidth: availableWidth
        clip: true
        padding: 60

        RowLayout {
            anchors.fill: parent
            spacing: 35

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: scrollView.availableWidth * 3/4
                spacing: 20

                anchors.leftMargin: 35
                anchors.rightMargin: 35
                anchors.topMargin: 30
                anchors.bottomMargin: 30

                Text {
                    text: qsTr("ProfitExpert")
                    font.pixelSize: 24
                    font.weight: Font.DemiBold
                    color: "#2c3e50"

                    Layout.fillWidth: true
                    Layout.bottomMargin: 5
                }

                GroupBox {
                    title: qsTr("Основная информация")
                    Layout.fillWidth: true

                    font.weight: Font.DemiBold
                    font.family: "sans-serif"
                    font.pixelSize: 14

                    padding: 15
                    topPadding: 35

                    background: Rectangle {
                        color: "#f4f6f9"
                        border.color: "#3498db"
                        border.width: 1
                        radius: 4
                    }

                    contentItem: GridLayout {
                        columns: 2
                        rowSpacing: 14
                        columnSpacing: 18

                        Text {
                            text: "Дело:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 12

                            TextField {
                                id: caseNameInput
                                placeholderText: "Название или суть дела"
                                Layout.fillWidth: true
                            }

                            TextField {
                                id: caseIDInput
                                placeholderText: "Рег. номер"
                                Layout.preferredWidth: 180
                            }
                        }

                        Text {
                            text: "Дата получения:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        Button {
                            id: dateButton
                            text: "Выбрать дату"
                            Layout.fillWidth: true
                            onClicked: mainDatePicker.open()
                        }

                        Text {
                            text: "Судья:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 12

                            TextField {
                                id: lawyerNameInput
                                placeholderText: "ФИО судьи"
                                Layout.fillWidth: true
                            }

                            Text {
                                text: "Тел.:"
                                color: "#555"
                            }

                            TextField {
                                id: lawyerNumberInput
                                inputMask: "+7 (000) 000-00-00;_"
                                Layout.preferredWidth: 180
                            }
                        }

                        Text {
                            text: "Суд:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 12

                            ComboBox {
                                model: [
                                    "Арбитражный",
                                    "Мировой",
                                    "Районный"
                                ]
                                Layout.fillWidth: true
                            }

                            Text {
                                text: "Адрес:"
                                color: "#555"
                            }

                            ComboBox {
                                model: [
                                    "ул. Ленина, 1",
                                    "пр. Мира, 45"
                                ]
                                Layout.preferredWidth: 180
                            }
                        }
                    }
                }

                GroupBox {
                    title: qsTr("Истец")
                    Layout.fillWidth: true

                    font.weight: Font.DemiBold
                    padding: 15
                    topPadding: 35

                    background: Rectangle {
                        color: "#f4f6f9"
                        border.color: "#3498db"
                        border.width: 1
                        radius: 4
                    }

                    contentItem: GridLayout {
                        columns: 2
                        rowSpacing: 14
                        columnSpacing: 18

                        Text {
                            text: "ФИО / Наименование:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: plaintiffName
                            placeholderText: "Иванов Иван Иванович"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Адрес:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: plaintiffAddress
                            placeholderText: "Город, улица, дом, квартира"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Телефон:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: plaintiffPhone
                            inputMask: "+7 (000) 000-00-00;_"
                            placeholderText: "+7 (***) *******-**"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Представитель:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: plaintiffRep
                            placeholderText: "ФИО представителя по доверенности"
                            Layout.fillWidth: true
                        }
                    }
                }

                GroupBox {
                    title: qsTr("Ответчик")
                    Layout.fillWidth: true

                    font.weight: Font.DemiBold
                    padding: 15
                    topPadding: 35

                    background: Rectangle {
                        color: "#f4f6f9"
                        border.color: "#3498db"
                        border.width: 1
                        radius: 4
                    }

                    contentItem: GridLayout {
                        columns: 2
                        rowSpacing: 14
                        columnSpacing: 18

                        Text {
                            text: "ФИО / Наименование:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: defendantName
                            placeholderText: "Петров Петр Петрович"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Адрес:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: defendantAddress
                            placeholderText: "Город, улица, дом, квартира"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Телефон:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: defendantPhone
                            inputMask: "+7 (000) 000-00-00;_"
                            placeholderText: "+7 (***) *******-**"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Представитель:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: defendantRep
                            placeholderText: "ФИО представителя"
                            Layout.fillWidth: true
                        }
                    }
                }

                GroupBox {
                    title: qsTr("Экспертиза")
                    Layout.fillWidth: true

                    font.weight: Font.DemiBold
                    padding: 15
                    topPadding: 35

                    background: Rectangle {
                        color: "#f4f6f9"
                        border.color: "#3498db"
                        border.width: 1
                        radius: 4
                    }

                    contentItem: GridLayout {
                        columns: 2
                        rowSpacing: 14
                        columnSpacing: 18

                        Text {
                            text: "Вид экспертизы:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: expertiseType
                            placeholderText: "Например: Строительно-техническая"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Предмет:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: expertiseSubject
                            placeholderText: "Объект исследования"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Эксперт:"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        ComboBox {
                            id: expertiseExpert

                            model: [
                                "Не назначен",
                                "Сидоров С.С.",
                                "ООО \"ГлавЭкспертиза\"",
                                "АНО \"Судэксперт\""
                            ]

                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Срок исполнения:"
                            color: "#555"
                            Layout.preferredWidth: 160
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
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: expertiseTravelCost
                            placeholderText: "0.00"
                            Layout.fillWidth: true

                            validator: RegularExpressionValidator {
                                regularExpression: /^\d+(\.\d{1,2})?$/
                            }
                        }

                        Text {
                            text: "Итог (₽):"
                            color: "#555"
                            Layout.preferredWidth: 160
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: expertiseTotalCost
                            placeholderText: "0.00"
                            Layout.fillWidth: true

                            validator: RegularExpressionValidator {
                                regularExpression: /^\d+(\.\d{1,2})?$/
                            }
                        }
                    }
                }
            }

            ColumnLayout {
                id: filesLayout
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: scrollView.availableWidth * 1/4
                spacing: 10

                Text {
                    text: qsTr("Шаблоны")
                    font.pixelSize: 16
                    font.weight: Font.DemiBold
                    color: "#2c3e50"
                    Layout.fillWidth: true
                    Layout.bottomMargin: 5
                }

                ListView {
                    id: filesListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    spacing: 2
                    focus: true

                    model: ListModel {
                        ListElement { name: "Bill Smith"; number: "555 3264"; checked: false }
                        ListElement { name: "John Brown"; number: "555 8426"; checked: false }
                        ListElement { name: "Sam Wise"; number: "555 0473"; checked: false }
                    }

                    delegate: CheckDelegate {
                        id: delegateItem
                        width: filesListView.width
                        height: 40
                        checkState: model.checked ? Qt.Checked : Qt.Unchecked
                        onToggled: {
                            model.checked = checkState === Qt.Checked
                        }

                        onClicked: {
                            filesListView.currentIndex = index
                        }

                        background: Rectangle {
                            color: delegateItem.highlighted || delegateItem.checked
                                   ? "#3498db"
                                   : (delegateItem.hovered
                                      ? "#e8f0fe"
                                      : "transparent")
                            radius: 6
                            border.color: delegateItem.highlighted ? "#2980b9" : "transparent"
                            border.width: 1
                        }

                        contentItem: RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12

                            Text {
                                Layout.fillWidth: true
                                text: model.name
                                font.pixelSize: 14
                                color: delegateItem.highlighted || delegateItem.checked ? "white" : "#2c3e50"
                                elide: Text.ElideRight
                                wrapMode: Text.NoWrap
                                verticalAlignment: Text.AlignVCenter
                            }

                            Text {
                                Layout.preferredWidth: 80
                                text: model.number
                                font.pixelSize: 12
                                color: delegateItem.highlighted || delegateItem.checked ? "#ecf0f1" : "#7f8c8d"
                                horizontalAlignment: Text.AlignVCenter
                                elide: Text.ElideRight
                                wrapMode: Text.NoWrap
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }

                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AsNeeded
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight: filesLayout.availableHeight * 3/4
                    spacing: 10

                    Button {
                        id: saveButton
                        Layout.fillWidth: true
                        Layout.preferredHeight: 42
                        hoverEnabled: true

                        background: Rectangle {
                            radius: 8
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: saveButton.pressed ? "#3498db" : "#3498db" }
                                GradientStop { position: 1.0; color: saveButton.pressed ? "#3498db" : "#2980b9" }
                            }
                            border.color: saveButton.hovered ? "#1f618d" : "#2471a3"
                            border.width: 1
                            opacity: saveButton.enabled ? 1.0 : 0.5
                        }

                        contentItem: RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12

                            Text {
                                text: "💾"
                                font.pixelSize: 18
                                color: "white"
                                Layout.preferredWidth: 24
                            }
                            Text {
                                text: qsTr("Сохранить")
                                font.pixelSize: 14
                                font.weight: Font.DemiBold
                                color: "white"
                                horizontalAlignment: Text.AlignLeft
                                Layout.fillWidth: true
                                elide: Text.ElideRight
                            }
                        }
                    }

                    Button {
                        id: loadButton
                        Layout.fillWidth: true
                        Layout.preferredHeight: 42
                        hoverEnabled: true

                        background: Rectangle {
                            radius: 8
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: loadButton.pressed ? "#3498db" : "#3498db" }
                                GradientStop { position: 1.0; color: loadButton.pressed ? "#3498db" : "#2980b9" }
                            }
                            border.color: loadButton.hovered ? "#1f618d" : "#2471a3"
                            border.width: 1
                        }

                        contentItem: RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12

                            Text {
                                text: "📂"
                                font.pixelSize: 18
                                color: "white"
                                Layout.preferredWidth: 24
                            }
                            Text {
                                text: qsTr("Загрузить")
                                font.pixelSize: 14
                                font.weight: Font.DemiBold
                                color: "white"
                                horizontalAlignment: Text.AlignLeft
                                Layout.fillWidth: true
                            }
                        }
                    }

                    Button {
                        id: openButton
                        Layout.fillWidth: true
                        Layout.preferredHeight: 42
                        hoverEnabled: true

                        background: Rectangle {
                            radius: 8
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: openButton.pressed ? "#1e6bb8" : "#3498db" }
                                GradientStop { position: 1.0; color: openButton.pressed ? "#155a9c" : "#2980b9" }
                            }
                            border.color: openButton.hovered ? "#1f618d" : "#2471a3"
                            border.width: 1
                        }

                        contentItem: RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12

                            Text {
                                text: "📁"
                                font.pixelSize: 18
                                color: "white"
                                Layout.preferredWidth: 24
                            }
                            Text {
                                text: qsTr("Открыть")
                                font.pixelSize: 14
                                font.weight: Font.DemiBold
                                color: "white"
                                horizontalAlignment: Text.AlignLeft
                                Layout.fillWidth: true
                            }
                        }
                    }
                }
            }
        }
    }

    DatePickerPopup {
        id: mainDatePicker

        onDateSelected: (dateText) => {
            dateButton.text = dateText
        }
    }

    DatePickerPopup {
        id: expDatePicker

        onDateSelected: (dateText) => {
            expDateButton.text = dateText
        }
    }
}
