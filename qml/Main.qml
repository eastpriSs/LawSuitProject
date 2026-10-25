import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform 1.1 as Platform

ApplicationWindow {
    width: 1150
    height: 750
    visible: true
    title: qsTr("Lawsuit Pro")
    color: StyleManager.background


    // todo убрать и сделать FolderDialog с автоматическим нахождением recovery.json
    Platform.FileDialog {
        id: fileDialog
        title: "Выберите файл для заполнения формы"
        onAccepted: {
            var filePath = fileDialog.file.toString();
            filePath = filePath.replace(/^file:\/\//, "")
            Presenter.loadRequested(filePath);
        }

    }

    Platform.FolderDialog {
        id: folderDialog
        title: "Выберите папку для сохранения"
        onAccepted: {

            var formData = {
            main: {
                caseName: caseNameInput.text,
                caseID: caseIDInput.text,
                dateReceived: dateButton.text,
                judgeName: lawyerNameInput.text,
                judgePhone: lawyerNumberInput.text,
                courtType: courtTypeCombo.currentText,
                judgeDate: dateButtonJudge.text
            },
            plaintiff: {
                name: plaintiffBox.plaintiffName,
                address: plaintiffBox.plaintiffAddress,
                phone: plaintiffBox.plaintiffPhone,
                representative: plaintiffBox.plaintiffRep,
                isPayer: plaintiffBox.plaintiffPay
            },
            defendant: {
                name: defendantBox.defendantName,
                address: defendantBox.defendantAddress,
                phone: defendantBox.defendantPhone,
                representative: defendantBox.defendantRep,
                isPayer: defendantBox.defendantPay
            },
            expertise: {
                type: expertiseBox.expertiseType,
                expert: expertiseBox.expertCurrentText,
                dueDate: expertiseBox.dateButtonText,
                travelCost: expertiseBox.travelCost,
                totalCost: expertiseBox.totalCost,
                totalCostWords: expertiseBox.totalCostWords,
                usdCost: expertiseBox.usdCost,
                usdCostWords: expertiseBox.usdCostWords,
                accountNumber: expertiseBox.accountNumberText,
                accountDate: expertiseBox.accountDateButtonText
            }
            };

            var folderPath = folderDialog.folder.toString()
            folderPath = folderPath.replace(/^file:\/\//, "")
            console.log("Выбрана папка:", folderPath)
            if (folderPath === "") {
                console.warn("Путь пустой")
                return
            }
            var files = FileModel.getCheckedFiles()
            Presenter.saveRequested(folderPath, files, formData)
        }
    }

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


    Connections {
        target: Presenter

        function onSuitDataLoaded(formData) {
            // main
            caseNameInput.text         = formData.main.caseName
            caseIDInput.text           = formData.main.caseID
            dateButton.text            = formData.main.dateReceived
            lawyerNameInput.text       = formData.main.judgeName
            lawyerNumberInput.text     = formData.main.judgePhone
            courtTypeCombo.displayText = formData.main.courtType
            dateButtonJudge.text       = formData.main.judgeDate || "Выбрать дату"

            // plaintiff
            plaintiffBox.plaintiffName    = formData.plaintiff.name
            plaintiffBox.plaintiffAddress = formData.plaintiff.address
            plaintiffBox.plaintiffPhone   = formData.plaintiff.phone
            plaintiffBox.plaintiffRep     = formData.plaintiff.representative
            plaintiffBox.plaintiffPay     = !!formData.plaintiff.isPayer

            // defendant
            defendantBox.defendantName    = formData.defendant.name
            defendantBox.defendantAddress = formData.defendant.address
            defendantBox.defendantPhone   = formData.defendant.phone
            defendantBox.defendantRep     = formData.defendant.representative
            defendantBox.defendantPay     = !!formData.defendant.isPayer

            // expertise
            expertiseBox.expertiseType        = formData.expertise.type
            expertiseBox.dateButtonText       = formData.expertise.dueDate
            expertiseBox.travelCost           = formData.expertise.travelCost
            expertiseBox.totalCost            = formData.expertise.totalCost
            expertiseBox.totalCostWords       = formData.expertise.totalCostWords || ""
            expertiseBox.usdCost              = formData.expertise.usdCost || ""
            expertiseBox.usdCostWords         = formData.expertise.usdCostWords || ""
            expertiseBox.accountNumberText    = formData.expertise.accountNumber || ""
            expertiseBox.accountDateButtonText = formData.expertise.accountDate || "Выбрать дату счёта"

            var idx = expertiseBox.expertModel.indexOf(formData.expertise.expert)
            if (idx !== -1)
                expertiseBox.expertCurrentIndex = idx
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
                            Text {
                                text: "Заявление №"
                                color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                       ? StyleManager.accentTextColor : StyleManager.secondaryText
                                font.weight: Font.Normal
                                Layout.preferredWidth: StyleManager.labelWidth
                                horizontalAlignment: Text.AlignRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextField { id: caseIDInput; placeholderText: "№"; Layout.preferredWidth: 180 }
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
                                id: courtTypeCombo
                                model: ["Суды АК с адресами"]
                                Layout.fillWidth: true
                                editable: true
                            }
                            Button {
                                id: editCourtModel
                                text: "+"
                            }
                        }
                        Text {
                            text: "Определение суда: "
                            color: (mainInfoGroupBox.isHighlightNeeded && Highlight.activeFields.indexOf(text) !== -1)
                                   ? StyleManager.accentTextColor : StyleManager.secondaryText
                            font.weight: Font.Normal
                            Layout.preferredWidth: StyleManager.labelWidth
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        Button {
                            id: dateButtonJudge
                            text: "Выбрать дату"
                            Layout.fillWidth: true
                            onClicked: judgeDatePicker.open()
                        }
                    }
                }

                PlaintiffGroupBox { id: plaintiffBox; Layout.fillWidth: true }
                DefendantGroupBox { id: defendantBox; Layout.fillWidth: true }
                ExpertiseGroupBox { id: expertiseBox; Layout.fillWidth: true }

                DatePickerPopup {
                    id: mainDatePicker
                    onDateSelected: (dateText) => { dateButton.text = dateText }
                }
                DatePickerPopup {
                    id: judgeDatePicker
                    onDateSelected: (dateText) => { dateButtonJudge.text = dateText }
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
                    onSaveClicked: folderDialog.open()
                    onLoadClicked: fileDialog.open()
                    onOpenClicked: {
                        var formData = {
                        main: {
                            caseName: caseNameInput.text,
                            caseID: caseIDInput.text,
                            dateReceived: dateButton.text,
                            judgeName: lawyerNameInput.text,
                            judgePhone: lawyerNumberInput.text,
                            courtType: courtTypeCombo.currentText,
                            judgeDate: dateButtonJudge.text
                        },
                        plaintiff: {
                            name: plaintiffBox.plaintiffName,
                            address: plaintiffBox.plaintiffAddress,
                            phone: plaintiffBox.plaintiffPhone,
                            representative: plaintiffBox.plaintiffRep,
                            isPayer: plaintiffBox.plaintiffPay
                        },
                        defendant: {
                            name: defendantBox.defendantName,
                            address: defendantBox.defendantAddress,
                            phone: defendantBox.defendantPhone,
                            representative: defendantBox.defendantRep,
                            isPayer: defendantBox.defendantPay
                        },
                        expertise: {
                            type: expertiseBox.expertiseType,
                            subject: expertiseBox.expertiseSubject,
                            expert: expertiseBox.expertCurrentText,
                            dueDate: expertiseBox.dateButtonText,
                            travelCost: expertiseBox.travelCost,
                            totalCost: expertiseBox.totalCost,
                            totalCostWords: expertiseBox.totalCostWords,
                            usdCost: expertiseBox.usdCost,
                            usdCostWords: expertiseBox.usdCostWords,
                            accountNumber: expertiseBox.accountNumberText,
                            accountDate: expertiseBox.accountDateButtonText
                        }
                        };
                        var files = FileModel.getCheckedFiles()
                        Presenter.openRequested(files, formData)
                    }
                }
            }
        }
    }
}
