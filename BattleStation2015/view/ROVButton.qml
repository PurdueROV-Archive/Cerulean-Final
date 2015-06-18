import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {

    property int fontSize: 30
    id: rovButton

    style: ButtonStyle {
        background: Rectangle {
            border.width: (rovButton.enabled) ? ((control.hovered || control.pressed) ? 2 : 1) : 1;
            color: (rovButton.enabled) ? ((control.hovered || control.pressed) ? "#222222" : "#111111") : "#111111"
            radius: 0
            border.color: mainColor
            opacity: rovButton.enabled ? 1.0 : 0.5
            implicitWidth: 70
            implicitHeight: 25
        }

        label: Label {
            text: control.text
            verticalAlignment: Text.AlignVCenter
            color: mainColor
            opacity: rovButton.enabled ? 1.0 : 0.5
            font.bold: true
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
