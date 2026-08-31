import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    property alias saveButton: saveBtn
    property alias loadButton: loadBtn
    property alias openButton: openBtn

    spacing: StyleManager.spacingTiny
    Layout.fillWidth: true

    signal saveClicked()

    Button {
        id: saveBtn
        Layout.fillWidth: true
        Layout.preferredHeight: StyleManager.buttonHeight
        hoverEnabled: true

        background: Rectangle {
            radius: 8
            gradient: Gradient {
                GradientStop { position: 0.0; color: saveBtn.pressed ? StyleManager.primaryDark : StyleManager.primaryColor }
                GradientStop { position: 1.0; color: saveBtn.pressed ? StyleManager.primaryDark : StyleManager.primaryDark }
            }
            border.color: saveBtn.hovered ? "#1f618d" : "#2471a3"
            border.width: 1
            opacity: saveBtn.enabled ? 1.0 : 0.5
        }

        contentItem: RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            Text { text: "💾"; font.pixelSize: 18; color: StyleManager.white; Layout.preferredWidth: 24 }
            Text { text: qsTr("Сохранить"); font.pixelSize: StyleManager.fontSizeNormal; font.weight: Font.DemiBold; color: StyleManager.white; horizontalAlignment: Text.AlignLeft; Layout.fillWidth: true; elide: Text.ElideRight }
        }

        onClicked: saveClicked()
    }

    Button {
        id: loadBtn
        Layout.fillWidth: true
        Layout.preferredHeight: StyleManager.buttonHeight
        hoverEnabled: true

        background: Rectangle {
            radius: 8
            gradient: Gradient {
                GradientStop { position: 0.0; color: loadBtn.pressed ? StyleManager.primaryDark : StyleManager.primaryColor }
                GradientStop { position: 1.0; color: loadBtn.pressed ? StyleManager.primaryDark : StyleManager.primaryDark }
            }
            border.color: loadBtn.hovered ? "#1f618d" : "#2471a3"
            border.width: 1
        }

        contentItem: RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            Text { text: "📂"; font.pixelSize: 18; color: StyleManager.white; Layout.preferredWidth: 24 }
            Text { text: qsTr("Загрузить"); font.pixelSize: StyleManager.fontSizeNormal; font.weight: Font.DemiBold; color: StyleManager.white; horizontalAlignment: Text.AlignLeft; Layout.fillWidth: true }
        }
    }

    Button {
        id: openBtn
        Layout.fillWidth: true
        Layout.preferredHeight: StyleManager.buttonHeight
        hoverEnabled: true

        background: Rectangle {
            radius: 8
            gradient: Gradient {
                GradientStop { position: 0.0; color: openBtn.pressed ? "#1e6bb8" : StyleManager.primaryColor }
                GradientStop { position: 1.0; color: openBtn.pressed ? "#155a9c" : StyleManager.primaryDark }
            }
            border.color: openBtn.hovered ? "#1f618d" : "#2471a3"
            border.width: 1
        }

        contentItem: RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            Text { text: "📁"; font.pixelSize: 18; color: StyleManager.white; Layout.preferredWidth: 24 }
            Text { text: qsTr("Открыть"); font.pixelSize: StyleManager.fontSizeNormal; font.weight: Font.DemiBold; color: StyleManager.white; horizontalAlignment: Text.AlignLeft; Layout.fillWidth: true }
        }
    }
}
