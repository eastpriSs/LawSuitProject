import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root

    property string headerText: "Редактировать список"
    property var initialItems: []

    signal itemsSaved(var items)

    parent: Overlay.overlay
    x: parent ? Math.round((parent.width - width) / 2) : 0
    y: parent ? Math.round((parent.height - height) / 2) : 0

    width: 420
    height: 480
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    title: headerText
    standardButtons: Dialog.NoButton

    ListModel { id: internalModel }

    onAboutToShow: {
        internalModel.clear()
        for (let i = 0; i < initialItems.length; ++i)
            internalModel.append({ value: String(initialItems[i]) })
        newItemField.text = ""
        newItemField.forceActiveFocus()
    }

    contentItem: ColumnLayout {
        spacing: 12

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            TextField {
                id: newItemField
                Layout.fillWidth: true
                placeholderText: qsTr("Новый элемент")
                onAccepted: addBtn.clicked()
            }
            Button {
                id: addBtn
                text: qsTr("Добавить")
                onClicked: {
                    const t = newItemField.text.trim()
                    if (t === "") return
                    internalModel.append({ value: t })
                    newItemField.text = ""
                    listView.positionViewAtEnd()
                }
            }
        }

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 1

            ListView {
                id: listView
                anchors.fill: parent
                anchors.margins: 8
                clip: true
                spacing: 4
                model: internalModel

                delegate: RowLayout {
                    width: listView.width
                    spacing: 6

                    TextField {
                        Layout.fillWidth: true
                        text: model.value
                        onEditingFinished: {
                            const v = text.trim()
                            if (v === "") internalModel.remove(index)
                            else           internalModel.setProperty(index, "value", v)
                        }
                    }
                    ToolButton {
                        text: "✕"
                        onClicked: internalModel.remove(index)
                    }
                }

                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            spacing: 8

            Button {
                text: qsTr("Отмена")
                onClicked: root.reject()
            }
            Button {
                text: qsTr("Сохранить")
                highlighted: true
                onClicked: {
                    const result = []
                    for (let i = 0; i < internalModel.count; ++i)
                        result.push(internalModel.get(i).value)
                    root.itemsSaved(result)
                    root.accept()
                }
            }
        }
    }
}
