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



    Tab {
        title: "Calculations"
        Item {
            anchors.fill: parent
            anchors.margins: 15

            Row {
                width: parent.width
                spacing: 10
                id: calcRow
                height: 150

                Item {
                    width: (parent.width/2) - 5
                    height: 100

                    Rectangle {
                        id: measure1
                        color: "white"
                        width: parent.width
                        height: 26
                        TextInput {
                            id: textMeasure1
                            anchors.margins: 3
                            text: "0"
                            color: "black"
                            anchors.fill: parent
                            font.family: roboto.name
                            font.pixelSize: 20
                            selectByMouse: true
                        }
                    }

                    ROVButton {
                        anchors.top: measure1.bottom
                        anchors.topMargin: 20
                        width: parent.width/2
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Copy laser"
                        height: 25
                        color: mainColor
                        fontSize: 20
                        onClicked: textMeasure1.text = controller.LaserDistance
                    }
                }

                Item {
                    width: (parent.width/2) - 5
                    height: 50

                    Rectangle {
                        id: measure2
                        color: "white"
                        width: parent.width
                        height: 26
                        TextInput {
                            id: textMeasure2
                            anchors.margins: 3
                            text: "0"
                            color: "black"
                            anchors.fill: parent
                            font.family: roboto.name
                            font.pixelSize: 20
                            selectByMouse: true
                        }
                    }

                    ROVButton {
                        anchors.top: measure2.bottom
                        anchors.topMargin: 20
                        width: parent.width/2
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Copy laser"
                        height: 25
                        color: mainColor
                        fontSize: 20
                        onClicked: textMeasure2.text = controller.LaserDistance
                    }
                }
            }
            Text {
                id: degrees
                width: parent.width
                anchors.top: calcRow.bottom
                anchors.topMargin: 20
                height: 20
                color: "white"
                font.pixelSize: 20
                text: Math.round(controller.StepperAngle*10)/10 + " degrees"
            }

            Text {
                id: formula
                width: parent.width
                anchors.top: degrees.bottom
                anchors.topMargin: 20
                height: 20
                color: "white"
                font.pixelSize: 20
                text: "c^2 = a^2 + b^2 - 2ab*cos(angleC)"
            }

            Text {
                id: result
                width: parent.width
                anchors.top: formula.bottom
                anchors.topMargin: 20
                height: 20
                color: "white"
                font.pixelSize: 20
                text: calculateLength();
            }

            ROVButton {
                anchors.top: result.bottom
                anchors.topMargin: 20
                anchors.left: parent.left
                width: 100
                text: "Calculate"
                height: 25
                color: mainColor
                fontSize: 20
                onClicked: result.text = calculateLength();
            }

            function calculateLength() {
                var a = parseInt(textMeasure1.text);
                var b = parseInt(textMeasure2.text);
                var cAngle = controller.StepperAngle;
                console.log(a, b, cAngle);
                return Math.sqrt(((a*a) + (b*b) - (2*a*b*Math.cos(cAngle))));
            }
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
                onValueChanged: controller.LEDControlScale(address, value)
                labeltext: "LED System " + address
            }

            ROVSlider {
                address: 2
                id: led2
                value: 0
                onValueChanged: controller.LEDControlScale(address, value)
                labeltext: "LED System " + address
            }

            ROVSlider {
                address: 3
                id: led3
                value: 0
                onValueChanged: controller.LEDControlScale(address, value)
                labeltext: "LED System " + address
            }
            ROVSlider {
                address: 4
                id: led4
                value: 0
                onValueChanged: controller.LEDControlScale(address, value)
                labeltext: "LED System " + address
            }
            ROVSlider {
                address: 5
                id: led5
                value: 0
                onValueChanged: controller.LEDControlScale(address, value)
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
                    onClicked: {
                        led1.value = 0
                        led2.value = 0
                        led3.value = 0
                        led4.value = 0
                        led5.value = 0
                    }
                }

                ROVButton {
                    anchors.left: zeroButton.right
                    anchors.right: fiftyButton.left
                    anchors.margins: 20

                    height: 30
                    fontSize: 20
                    text: "25%"
                    onClicked: {
                        led1.value = 25
                        led2.value = 25
                        led3.value = 25
                        led4.value = 25
                        led5.value = 25
                    }
                }

                ROVButton {
                    id: fiftyButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.buttonSize

                    height: 30
                    fontSize: 20
                    text: "50%"
                    onClicked: {
                         led1.value = 50
                         led2.value = 50
                         led3.value = 50
                         led4.value = 50
                         led5.value = 50
                    }
                }

                ROVButton {
                    anchors.left: fiftyButton.right
                    anchors.right: hundredButton.left
                    anchors.margins: 20

                    height: 30
                    fontSize: 20
                    text: "75%"
                    onClicked: {
                         led1.value = 75
                         led2.value = 75
                         led3.value = 75
                         led4.value = 75
                         led5.value = 75
                    }
                }

                ROVButton {
                    id: hundredButton
                    anchors.right: parent.right
                    width: parent.buttonSize

                    height: 30
                    fontSize: 20
                    text: "100%"
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
