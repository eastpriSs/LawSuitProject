import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: calendarPopup

    signal dateSelected(string dateText)

    x: parent ? Math.round((parent.width - width) / 2) : 0
    y: parent ? Math.round((parent.height - height) / 2) : 0

    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property int currentMonth: new Date().getMonth()
    property int currentYear: new Date().getFullYear()

    onOpened: {
        currentMonth = new Date().getMonth()
        currentYear = new Date().getFullYear()
    }

    ColumnLayout {
        spacing: 10

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "<"
                onClicked: {
                    if (calendarPopup.currentMonth === 0) {
                        calendarPopup.currentMonth = 11
                        calendarPopup.currentYear--
                    } else {
                        calendarPopup.currentMonth--
                    }
                }
            }

            Text {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 14
                text: {
                    let months = ["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                                  "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"]
                    return months[calendarPopup.currentMonth] + " " + calendarPopup.currentYear
                }
            }

            Button {
                text: ">"
                onClicked: {
                    if (calendarPopup.currentMonth === 11) {
                        calendarPopup.currentMonth = 0
                        calendarPopup.currentYear++
                    } else {
                        calendarPopup.currentMonth++
                    }
                }
            }
        }

        DayOfWeekRow {
            locale: monthGrid.locale
            Layout.fillWidth: true
        }

        MonthGrid {
            id: monthGrid
            month: calendarPopup.currentMonth
            year: calendarPopup.currentYear
            locale: Qt.locale("ru_RU")
            Layout.fillWidth: true

            onClicked: (date) => {
                let formattedDate = date.toLocaleDateString(Qt.locale("ru_RU"), "dd.MM.yyyy")
                calendarPopup.dateSelected(formattedDate)
                calendarPopup.close()
            }
        }
    }
}
