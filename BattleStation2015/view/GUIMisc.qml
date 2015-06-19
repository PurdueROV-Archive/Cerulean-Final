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
                id: led1
                value: 0
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }

            ROVSlider {
                address: 2
                id: led2
                value: 0
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }

            ROVSlider {
                address: 3
                id: led3
                value: 0
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }
            ROVSlider {
                address: 4
                id: led4
                value: 0
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }
            ROVSlider {
                address: 5
                id: led5
                value: 0
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "LED System " + address
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 30

                property int buttonSize: Math.round((width-(20*4)) / 5)

                ROVButton {
                    id: zeroButton
                    anchors.left: parent.left
                    width: parent.buttonSize

                    height: 30
                    fontSize: 20
                    text: "0%"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            led1.value = 0
                            led2.value = 0
                            led3.value = 0
                            led4.value = 0
                            led5.value = 0
                        }
                    }
                }

                ROVButton {
                    anchors.left: zeroButton.right
                    anchors.right: fiftyButton.left
                    anchors.margins: 20

                    height: 30
                    fontSize: 20
                    text: "25%"
                    MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             led1.value = 25
                             led2.value = 25
                             led3.value = 25
                             led4.value = 25
                             led5.value = 25
                         }
                     }
                }

                ROVButton {
                    id: fiftyButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.buttonSize

                    height: 30
                    fontSize: 20
                    text: "50%"
                    MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             led1.value = 50
                             led2.value = 50
                             led3.value = 50
                             led4.value = 50
                             led5.value = 50
                         }
                     }
                }

                ROVButton {
                    anchors.left: fiftyButton.right
                    anchors.right: hundredButton.left
                    anchors.margins: 20

                    height: 30
                    fontSize: 20
                    text: "75%"
                    MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             led1.value = 75
                             led2.value = 75
                             led3.value = 75
                             led4.value = 75
                             led5.value = 75
                         }
                     }
                }

                ROVButton {
                    id: hundredButton
                    anchors.right: parent.right
                    width: parent.buttonSize

                    height: 30
                    fontSize: 20
                    text: "100%"
                    MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             led1.value = 100
                             led2.value = 100
                             led3.value = 100
                             led4.value = 100
                             led5.value = 100
                         }
                     }
                }
            }
        }
    }
}
