import QtQuick 2.4

ROVBox {
    id: sysStatus
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    clip: true

    height: (parent.height/2) - 10

    ROVTitle {
        id: sysStatusTitle
        text: "SYSTEM STATUS"
    }

    Flickable {
        width: sysStatus.width
        height: sysStatus.height
        flickableDirection: Flickable.VerticalFlick
        contentHeight: thrusterControl.height+80
        contentWidth: thrusterControl.width
        boundsBehavior: Flickable.StopAtBounds
        clip: true


        Column {
            id: thrusterControl
            width: sysStatus.width-55
            spacing: 10
            y: 20
            clip: true

            ROVSlider {
                address: 1
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }

            ROVSlider {
                address: 2
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }

            ROVSlider {
                address: 3
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }
            ROVSlider {
                address: 4
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }

            ROVSlider {
                address: 5
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }

            ROVSlider {
                address: 6
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }

            ROVSlider {
                address: 7
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }
            ROVSlider {
                address: 8
                onValueChanged: controller.thrusterControlMax(address, value)
                labeltext: "Thruster " + address + ":"
            }
        }
    }

}
