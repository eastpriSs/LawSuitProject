import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    width: 850
    height: 750
    visible: true
    title: qsTr("Lawsuit Pro")
    color: StyleManager.background


    Dialog {
        id: errorDialog
        title: "Ошибка"
        modal: true
        standardButtons: Dialog.Ok
        width: 400
        property string message: ""
        contentItem: Label {
            text: errorDialog.message
            wrapMode: Text.Wrap
        }
    }

    Connections {
        target: errorHandler

        function onShowErrorDialog(title, message) {
            errorDialog.title = title
            errorDialog.message = message
            errorDialog.open()
        }
    }


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

                Row {
                    spacing: 70
                    Text {
                        text: qsTr("ProfitExpert")
                        font.pixelSize: StyleManager.fontSizeLarge
                        font.weight: Font.DemiBold
                        color: StyleManager.textColor
                        Layout.fillWidth: true
                        Layout.bottomMargin: 5
                    }

                    Rectangle {
                        id: statusBadge
                        Layout.alignment: Qt.AlignRight
                        height: 32
                        width: statusLabel.implicitWidth + 32
                        radius: 6
                        color: StyleManager.primaryLight
                        border.color: StyleManager.textColor
                        border.width: 1

                        Row {
                            anchors.centerIn: parent
                            spacing: 6

                            Rectangle {
                                width: 10
                                height: 10
                                radius: 5
                                color: statusBadge.border.color
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Text {
                                id: statusLabel
                                text: errorHandler.appState
                                color: StyleManager.textColor
                            }
                        }
                    }
                }

                CustomGroupBox {
                    id: mainInfoGroupBox
                    title: "Основная информация"
                    readonly property bool isHighlightNeeded: Highlight.activeFields.indexOf(title) !== -1
                    Layout.fillWidth: true

                    GridLayout {
                        anchors.fill: parent
                        columns: 2
                        rowSpacing: 14
                        columnSpacing: 18

                        Text {
                            text: "Дело:"
                            color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                   ? StyleManager.accentTextColor : StyleManager.secondaryText
                            font.weight: Font.Normal
                            Layout.preferredWidth: StyleManager.labelWidth
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: StyleManager.spacingSmall
                            TextField { id: caseNameInput; placeholderText: "Название"; Layout.fillWidth: true }
                            TextField { id: caseIDInput; placeholderText: "Рег. номер"; Layout.preferredWidth: 180 }
                        }

                        Text {
                            text: "Дата получения:"
                            color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                   ? StyleManager.accentTextColor : StyleManager.secondaryText
                            font.weight: Font.Normal
                            Layout.preferredWidth: StyleManager.labelWidth
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
                            color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                   ? StyleManager.accentTextColor : StyleManager.secondaryText
                            font.weight: Font.Normal
                            Layout.preferredWidth: StyleManager.labelWidth
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: StyleManager.spacingSmall
                            TextField { id: lawyerNameInput; placeholderText: "ФИО судьи"; Layout.fillWidth: true }
                            Text {
                                text: "Тел.:"
                                color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                       ? StyleManager.accentTextColor : StyleManager.secondaryText
                                font.weight: Font.Normal
                            }
                            TextField { id: lawyerNumberInput; inputMask: "+7 (000) 000-00-00;_"; Layout.preferredWidth: StyleManager.phoneWidth }
                        }

                        Text {
                            text: "Суд:"
                            color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                   ? StyleManager.accentTextColor : StyleManager.secondaryText
                            font.weight: Font.Normal
                            Layout.preferredWidth: StyleManager.labelWidth
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: StyleManager.spacingSmall
                            ComboBox {
                                model: ["Арбитражный", "Мировой", "Районный"]
                                Layout.fillWidth: true
                            }
                            Text {
                                text: "Адрес:"
                                color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                       ? StyleManager.accentTextColor : StyleManager.secondaryText
                                font.weight: Font.Normal
                            }
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
