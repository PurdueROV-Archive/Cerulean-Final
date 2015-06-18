import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVBox {
    id: orientationStatus
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: (parent.height/2) - 10

    ROVTitle {
        id: thrusterTitle
        text: "Thrusters"
    }

    TabView {
        id: thrusterTabs
        anchors.top: thrusterTitle.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width-30
        height: parent.height-40
        clip: true

        style: TabViewStyle {
            frameOverlap: 1
            tab: ROVTab {
                color: styleData.selected ? "#222222" :"#000000"
                clip: true
                implicitWidth: (thrusterTabs.width)/3
                implicitHeight: 40
            }

            frame: Rectangle {color: "transparent" }
        }

        //Thruster View
        Tab {
            title: "View"
            Item {
                anchors.fill: parent
                anchors.bottomMargin: 20

                Grid {
                    width: 280
                    height: 280
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    antialiasing: true
                    columns: 2
                    rows: 2
                    spacing: 100
                    ROVThruster {
                        objectName: "t7";
                        orientation: "horizontal";
                        rotation: 23;
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t2";
                        orientation: "horizontal";
                        rotation: -23;
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t5";
                        orientation: "horizontal";
                        rotation: 157;
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t4";
                        orientation: "horizontal";
                        rotation: 203;
                        value: qsTr("N/A")
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
                        objectName: "t8";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t9";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t9";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                    ROVThruster {
                        objectName: "t3";
                        orientation: "vertical";
                        value: qsTr("N/A")
                    }
                }
            }

        }

        //Speed Controls
        Tab {
            title: "Speed Control"

            ROVScrollingBox {
                anchors.fill: parent
                anchors.margins: 20
                anchors.bottomMargin: 20

                ROVSlider {
                    address: 1
                    onValueChanged: controller.ThrusterControlScale(address, value)
                    labeltext: "Horizontal Speed Control:"
                }

                ROVSlider {
                    address: 2
                    onValueChanged: controller.ThrusterControlScale(address, value)
                    labeltext: "Vertical Speed Control:"
                }

                ROVSlider {
                    address: 3
                    onValueChanged: controller.ThrusterControlScale(address, value)
                    labeltext: "Strafe Speed Control:"
                }
                ROVSlider {
                    address: 4
                    onValueChanged: controller.ThrusterControlScale(address, value)
                    labeltext: "Pitch/Roll Speed Control:"
                }
            }
        }

        //Ind Toggles
        Tab {
            title: "Indvidual Control"

            ROVScrollingBox {
                anchors.fill: parent
                anchors.margins: 20
                anchors.bottomMargin: 20

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
}
