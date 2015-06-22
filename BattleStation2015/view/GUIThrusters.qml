import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVCardTab {
    id: thrusters
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: (parent.height/2) - 10

    title: "Thrusters"
    headerColor: mainColor
    accent: mainAccent

    //Thruster View
    Tab {
        title: "View"
        Item {
            anchors.fill: parent
            anchors.margins: 15

            Grid {
                id: horizontalThrusters
                width: 280
                height: 280
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                antialiasing: true
                columns: 2
                rows: 2
                spacing: 100
                ROVThruster {
                    orientation: "horizontal";
                    rotation: 23;
                    value: "N/A"
                }
                ROVThruster {
                    orientation: "horizontal";
                    rotation: -23;
                    value: "N/A"
                }
                ROVThruster {
                    orientation: "horizontal";
                    rotation: 157;
                    value: "N/A"
                }
                ROVThruster {
                    orientation: "horizontal";
                    rotation: 203;
                    value: "N/A"
                }

            }

            Grid {
                width: 182
                height: 182
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                antialiasing: true
                columns: 2
                rows: 2
                spacing: 2
                ROVThruster {
                    orientation: "vertical";
                    value: "N/A"
                }
                ROVThruster {
                    orientation: "vertical";
                    value: "N/A"
                }
                ROVThruster {
                    orientation: "vertical";
                    value: "N/A"
                }
                ROVThruster {
                    orientation: "vertical";
                    value: "N/A"
                }
            }

            //Horizontal Status
            Column {
                spacing: 25
                anchors.left: parent.left
                anchors.right: horizontalThrusters.left
                clip: true

                Text {
                    text: "H Status"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                }

                Text {
                    text: "Front Left:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                }

                Text {
                    text: "Front Right:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                }

                Text {
                    text: "Back Left:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                }

                Text {
                    text: "Back Right:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                }
            }

            //Horizontal Status
            Column {
                spacing: 25
                anchors.left: horizontalThrusters.right
                anchors.right: parent.right
                clip: true

                Text {
                    text: "V Status"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                }

                Text {
                    text: "Front Left:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                }

                Text {
                    text: "Front Right:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                }

                Text {
                    text: "Back Left:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                }

                Text {
                    text: "Back Right:\n" + "Good"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                }
            }

        }

    }

    //Speed Controls
    Tab {
        title: "Speed Control"

        ROVScrollingBox {
            anchors.fill: parent
            anchors.margins: 15

            ROVSlider {
                address: 1
                onValueChanged: controller.ThrusterScaleGroups("horizontoal", value)
                labeltext: "Horizontal Speed Control:"
            }

            ROVSlider {
                address: 2
                onValueChanged: controller.ThrusterScaleGroups("vertical", value)
                labeltext: "Vertical Speed Control:"
            }

            ROVSlider {
                address: 3
                onValueChanged: controller.ThrusterScaleGroups("strafe", value)
                labeltext: "Strafe Speed Control:"
            }
            ROVSlider {
                address: 4
                onValueChanged: controller.ThrusterScaleGroups("pitchroll", value)
                labeltext: "Pitch/Roll Speed Control:"
            }
        }
    }

    //Ind Toggles
    Tab {
        title: "Individual Control"

        ROVScrollingBox {
            anchors.fill: parent
            anchors.margins: 15

            ROVSlider {
                address: 1
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (H-FL):"
            }

            ROVSlider {
                address: 2
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (H-FR):"
            }

            ROVSlider {
                address: 3
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (H-BL):"
            }
            ROVSlider {
                address: 4
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (H-BR):"
            }

            ROVSlider {
                address: 5
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (V-FL):"
            }

            ROVSlider {
                address: 6
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (V-FR):"
            }

            ROVSlider {
                address: 7
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (V-BL):"
            }
            ROVSlider {
                address: 8
                onValueChanged: controller.ThrusterControlScale(address, value)
                labeltext: "Thruster " + address + " (V-BR):"
            }
        }
    }

}
