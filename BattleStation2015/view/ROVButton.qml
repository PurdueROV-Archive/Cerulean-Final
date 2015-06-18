import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {

    property int fontSize: 30
    id: rovButton

    style: ButtonStyle {
        background: Rectangle {
            border.width: (rovButton.enabled) ? ((control.hovered || control.pressed) ? 2 : 1) : 1;
            color: (rovButton.enabled) ? ((control.hovered || control.pressed) ? "#111111" : "#00000000") : "#00000000"
            radius: 0
            border.color: (rovButton.enabled) ? mainColor : "#0C253B"
            implicitWidth: 70
            implicitHeight: 25
        }
        label: Label {
            text: control.text
            verticalAlignment: Text.AlignVCenter
            color: (rovButton.enabled) ? mainColor : "#0C253B"
            font.bold: true
            font.pixelSize: fontSize
            font.family: "Arial"
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
