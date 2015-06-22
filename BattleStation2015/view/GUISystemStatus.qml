import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVCard {
    id: systemStatus
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: (parent.height/2) - 10

    title: "System Status"
    headerColor: mainColor

    Row {
        id: row
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 20

        Column {
            spacing: 30
            width: row.width/2 - 10
            clip: true

            //Camera Selection
            Item {
                height: 60
                width: parent.width

                Text {
                    text: "Primary Camera Select"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20

                    id: cam1Label
                }

                property bool currentIndex: controller.CameraSelect1;
                onCurrentIndexChanged: {
                    frontCam.checked = !controller.CameraSelect1;
                    backCam.checked = controller.CameraSelect1;
                }

                Row {
                    anchors.top: cam1Label.bottom
                    anchors.topMargin: 10
                    spacing: 30
                    ExclusiveGroup {
                        id: camSelect1
                    }

                    ROVRadio {
                        id: frontCam
                        text: "Front"
                        size: 20
                        checked: !controller.CameraSelect1;
                        exclusiveGroup: camSelect1
                        onClicked: {
                            controller.CameraSelect1 = false;
                        }
                    }


                    ROVRadio {
                        id: backCam
                        text: "Back"
                        size: 20
                        checked: controller.CameraSelect1;
                        exclusiveGroup: camSelect1
                        onClicked: {
                            controller.CameraSelect1 = true;
                        }
                    }
                }
            }

            //Foot Turner
            Item {
                height: 60
                width: parent.width
                Text {
                    text: "Valve Turner"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20

                    id: valveTurnerLabel
                }

                ROVCheckBox {
                    anchors.top: valveTurnerLabel.bottom
                    anchors.topMargin: 10
                    size: 20
                    checked: false
                    text: (checked) ? "100%!!!" : "Off"
                }
            }

            //Laser
            Item {
                height: 60
                width: parent.width
                Text {
                    text: "Laser"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20

                    id: laserLabel
                }

                ROVCheckBox {
                    anchors.top: laserLabel.bottom
                    anchors.topMargin: 10
                    size: 20
                    checked: controller.LaserEnabled
                    MouseArea {
                        anchors.fill: parent
                        preventStealing: true;
                        onClicked: {
                            controller.LaserEnabled = !controller.LaserEnabled
                        }
                    }

                    text: (checked) ? controller.LaserDistance + " mm" : "Off"
                }
            }

        }

        Column {
            spacing: 25
            width: row.width/2 - 10
            clip: true

            //Camera Selection
            Item {
                height: 60
                width: parent.width

                Text {
                    text: "Secondary Camera Select"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20

                    id: cam2Label
                }

                property bool currentIndex: controller.CameraSelect2;
                onCurrentIndexChanged: {
                    leftCam.checked = !controller.CameraSelect2;
                    rightCam.checked = controller.CameraSelect2;
                }

                Row {
                    anchors.top: cam2Label.bottom
                    anchors.topMargin: 10
                    spacing: 30
                    ExclusiveGroup {
                        id: camSelect2
                    }

                    ROVRadio {
                        id: leftCam
                        text: "Left"
                        size: 20
                        exclusiveGroup: camSelect2
                        checked: !controller.CameraSelect2;
                        onClicked: {
                            controller.CameraSelect2 = false;
                        }
                    }


                    ROVRadio {
                        id: rightCam
                        text: "Right"
                        size: 20
                        exclusiveGroup: camSelect2
                        checked: controller.CameraSelect2;
                        onClicked: {
                            controller.CameraSelect2 = true;
                        }
                    }
                }
            }

            //Bilge Pump Motor
            Item {
                height: 60
                width: parent.width
                Text {
                    text: "Bilge Pump"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20

                    id: bilgeLabel
                }

                Row {
                    anchors.top: bilgeLabel.bottom
                    anchors.topMargin: 10
                    spacing: 30
                    ExclusiveGroup {
                        id: bilgeSelect
                    }

                    ROVRadio {
                        text: "Off"
                        size: 20
                        checked: true
                        exclusiveGroup: bilgeSelect
                    }


                    ROVRadio {
                        text: "Suck"
                        size: 20
                        exclusiveGroup: bilgeSelect
                    }

                    ROVRadio {
                        text: "Push"
                        size: 20
                        exclusiveGroup: bilgeSelect
                    }
                }
            }

            //Fuse Detection
            Item {
                height: 60
                width: parent.width
                Text {
                    text: "Fuse Dectection"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20

                    id: fuseLabel
                }

                Text {
                    anchors.top: fuseLabel.bottom
                    anchors.topMargin: 10
                    text: "Status: " + "Okay!"
                    font.family: roboto.name
                    color: "white"
                    font.pixelSize: 20
                }
            }
        }
    }

    Item {
        id: voltageDisplay
        anchors.top: row.bottom
        anchors.topMargin: 25

        height: 100
        width: parent.width

        ROVCheckBox {
            anchors.horizontalCenter: parent.horizontalCenter

            id: voltageLabel
            size: 20
            checked: false
            text: "Voltage Measurement Detection"
        }

        Row {
            anchors.top: voltageLabel.bottom
            anchors.topMargin: 10
            width: parent.width
            visible: voltageLabel.checked

            Text {
                text: "Top: " + "High"
                font.family: roboto.name
                color: "white"
                font.pixelSize: 20
                width: parent.width/3
                horizontalAlignment: Text.AlignHCenter
            }


            Text {
                text: "Center: " + "Low"
                font.family: roboto.name
                color: "white"
                font.pixelSize: 20
                width: parent.width/3
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "Bottom: " + "High"
                font.family: roboto.name
                color: "white"
                font.pixelSize: 20
                width: parent.width/3
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
