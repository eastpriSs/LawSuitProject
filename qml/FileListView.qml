import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: listView
    clip: true
    spacing: 2
    focus: true

    delegate: ItemDelegate {
        id: delegateItem
        width: listView.width
        height: StyleManager.rowHeight
        highlighted: ListView.isCurrentItem

        background: Rectangle {
            color: checkBox.checked ? StyleManager.primaryColor
                   : (delegateItem.hovered ? StyleManager.primaryLight : "transparent")
            radius: 6
            border.color: checkBox.checked ? StyleManager.primaryDark
                    : (delegateItem.hovered ? StyleManager.primaryLight : "transparent")
            border.width: 1
        }

        contentItem: Row {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12

            CheckBox {
                id: checkBox
                checked: model.checked
                onToggled: {
                    if (typeof model.setItemChecked === "function") {
                        model.setItemChecked(index, checked)
                    }
                }
                Layout.alignment: Qt.AlignLeft
            }

            Text {
                Layout.fillWidth: true
                text: model.name
                font.pixelSize: StyleManager.fontSizeNormal
                color: checkBox.checked ? StyleManager.white : StyleManager.textColor
            }
            Text {
                Layout.preferredWidth: 80
                text: model.number
                font.pixelSize: StyleManager.fontSizeSmall
                color: checkBox.checked ? "#ecf0f1" : StyleManager.lightText
            }
        }

        onClicked: {
            listView.currentIndex = index
            checkBox.toggle()
        }
    }

    ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }
}
