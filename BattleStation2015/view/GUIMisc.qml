import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVCardTab {
    id: misc
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    //clip: true

    height: (parent.height/2) - 10

    title: "Calculations/Misc"
    headerColor: mainColor
    accent: mainAccent

    //Mission 1 Tasks
    Tab {
        title: "Calculations"
        Label {
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            color: "white"
            font.pixelSize: 40
            text: "Do calculations and stuffs"
        }
    }

    Tab {
        title: "LED Control"
        ROVScrollingBox {
            anchors.fill: parent
            anchors.margins: 15

            ROVSlider {
                address: 1
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }

            ROVSlider {
                address: 2
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }

            ROVSlider {
                address: 3
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }
            ROVSlider {
                address: 4
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }
            ROVSlider {
                address: 5
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }
        }
    }
}
