import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVBox {
    id: missionTasks
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10

    height: parent.height - timerArea.height-20

    ROVTitle {
        id: missionTasksTitle
        text: "Mission Tasks"
    }

    TabView {
        id: missionTasksTab
        anchors.top: missionTasksTitle.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width-30
        height: parent.height
        clip: true

        style: TabViewStyle {
            frameOverlap: 1
            tab: ROVTab {
                //color: styleData.selected ? "#222222" :"#111111"
                clip: true
                implicitWidth: (missionTasksTab.width)/3
                implicitHeight: 50
            }

            frame: Rectangle {color: "transparent" }
        }

        //Mission 1 Tasks
        Tab {
            title: "Science Under the Ice"
            MissionTasks1 {}

        }

        //Mission 2 Tasks
        Tab {
            title: "Pipeline Inspection & Repair"
            MissionTasks2 {}
        }

        //Mission 3 Tasks
        Tab {
            title: "Oilfield Prod & Maintenance"
            MissionTasks3 {}
        }
    }
}
