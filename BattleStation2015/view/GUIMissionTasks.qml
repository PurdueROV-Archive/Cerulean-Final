import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0


ROVCardTab {
    id: missionTasks
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    //clip: true

    height: parent.height - 130

    title: "Mission Tasks"
    headerColor: mainColor
    accent: mainAccent

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
