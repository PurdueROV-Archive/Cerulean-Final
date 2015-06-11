import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVBox {
    id: configuration
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: (parent.height/2) - 10

    ROVTitle {
        id: configurationTitle
        text: "CONFIGURATION"
    }

    TabView {
        id: configurationTab
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: configurationTitle.bottom
        width: parent.width-30
        height: parent.height
        clip: true

        style: TabViewStyle {
            frameOverlap: 1
            tab: ROVTab {
                color: styleData.selected ? "#222222" :"#000000"
                clip: true
                implicitWidth: (configurationTab.width)/3
                implicitHeight: 50
            }

            frame: Rectangle {color: "transparent" }
        }

        //Configuration 1
        Tab {
            id: tab1
            title: "Speed Control"

            Column {
                id: speedcontrol
                spacing: 10
                y: 20

                ROVSlider {
                    labeltext: "Horizontal Speed Control:"
                    objectName: "horizontalSlider"
                }

                ROVSlider {
                    labeltext: "Vertical Speed Control:"
                    objectName: "verticalSlider"
                }

                ROVSlider {
                    labeltext: "Strafe Speed Control:"
                    objectName: "strafeSlider"
                }

                ROVSlider {
                    labeltext: "Pitch/Roll Speed Control:"
                    objectName: "pitchRollSlider"
                }
            }
        }

        //Configuration 2
        Tab {

            title: "Serial and Controller"
            Column {
                id: configsettings2
                y: 20
                spacing: 10

                Label {
                    text: "Serial Device:"
                    anchors.left: parent.left;
                    anchors.right: parent.right
                    font.bold: true
                    font.pixelSize: 18
                    color: "white"
                }

                ComboBox {
                    id: serialCombo
                    height: 30
                    anchors.left: parent.left;
                    anchors.right: parent.right
                    model: controller.SerialDevices
                    enabled: !controller.Running
                    onCurrentIndexChanged: controller.SerialSelect(currentIndex)
                }

                Label {
                    text: "Joystick 1:"
                    anchors.left: parent.left;
                    anchors.right: parent.right

                    font.bold: true
                    font.pixelSize: 18
                    color: "white"
                }

                ComboBox {
                    id: joystick1Combo
                    height: 30
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    model: controller.JoystickDevices
                    enabled: !controller.Running
                    onModelChanged: if (count == 0) currentIndex = -1;
                    onCurrentIndexChanged: {
                        controller.Joystick1Select(currentIndex)
                        if (joystick2Combo.currentIndex == currentIndex && joystick2Combo.currentIndex != -1)
                            joystick2Combo.currentIndex = -1;
                    }
                }

                Label {
                    text: "Joystick 2:"
                    anchors.left: parent.left;
                    anchors.right: parent.right
                    font.bold: true
                    font.pixelSize: 18
                    color: "white"
                }

                ComboBox {
                    id: joystick2Combo
                    height: 30
                    anchors.left: parent.left;
                    anchors.right: parent.right
                    model: controller.JoystickDevices
                    enabled: !controller.Running
                    onModelChanged: if (count == 0) currentIndex = -1;
                    onCurrentIndexChanged: {
                        controller.Joystick2Select(currentIndex)
                        if (joystick1Combo.currentIndex == currentIndex && joystick1Combo.currentIndex != -1)
                            joystick1Combo.currentIndex = -1;
                    }
                 }


                Row {
                    width: 320
                    height: 30
                    spacing: 20

                    anchors.horizontalCenter: parent.horizontalCenter

                    ROVButton {
                        id: refresh
                        height: 30
                        width: 150
                        text: "Refresh"
                        fontSize: 20
                        enabled: !controller.Running
                        onClicked: controller.RefreshLists()
                    }

                    ROVButton {
                        id: serialControl
                        height: 30
                        width: 150

                        text: (!controller.Running) ? "Connect" : "Stop"
                        fontSize: 20
                        onClicked: {
                            if (joystick1Combo.currentIndex >= 0)
                                controller.Running = !controller.Running
                        }
                    }
                }
            }
        }

        //Configuration 3
        Tab {
            id: tab3
            title: "Speed Control"
            objectName: "thrusterSliders"
        }
    }
}
