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
                spacing: 20

                ROVButton {
                    id: serialControl
                    height: 70
                    width: 150
                    text: qsTr("Start")
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        controller.running = !controller.running;
                        console.log(controller.running);
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
