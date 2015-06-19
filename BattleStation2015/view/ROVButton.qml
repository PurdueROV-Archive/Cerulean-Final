import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {

    property int fontSize: 30
    property string color: mainColor

    id: rovButton

    style: ButtonStyle {
        background: Rectangle {
            //border.width: (rovButton.enabled) ? ((control.hovered || control.pressed) ? 2 : 1) : 1;
            //color: (rovButton.enabled) ? ((control.hovered || control.pressed) ? "#222222" : "#111111") : "#111111"
            radius: 2
            color: (rovButton.enabled) ? rovButton.color : "#bbbbbb"

            Rectangle {
                anchors.fill: parent
                color: "white"
                opacity: (control.hovered) ? 0.3 : 0.0
                Behavior on opacity {NumberAnimation {duration: 300}}
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.bottom
                height: 10
                radius: 2
                gradient: Gradient {
                     GradientStop { position: 0.0; color: "#33000000" }
                     GradientStop { position: 1.0; color: "#00000000" }
                 }

                opacity: (control.hovered) ? 1 : 0.0
                Behavior on opacity {NumberAnimation {duration: 300}}
            }

        }

        label: Label {
            text: control.text
            verticalAlignment: Text.AlignVCenter
            color: (rovButton.enabled) ? "white" : "#999999"
            font.family: roboto.name
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
