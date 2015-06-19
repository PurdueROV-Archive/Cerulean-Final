import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Item {
    anchors.fill: parent
    anchors.margins: 15

    ROVScrollingBox {
        id: taskList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: points.top

        clip: true

        spacing: 20

        property int value: {
            (task1.value)  + (task2.value)  + (task3.value)  +
            (task4.value)  + (task5.value)  + (task6.value)  +
            (task7.value)  + (task8.value)  + (task9.value)  +
            (task10.value) + (task11.value) + (task12.value) +
            (task13.value) + (task14.value)
        }

        ROVMissionTask {
            id: task1
            text: "Find corroded pipe section - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task2
            text: "Turn valve to stop oil flow - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task3
            text: "Verify gauge pressure is zero - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task4
            text: "Measure corroded pipe section - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task5
            text: "Attach lift line to corroded section - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task6
            text: "Pull pins to cut corroded section (2 parts) - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task7
            text: "Remove corroded pipe to surface - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task8
            text: "Install flange adapter (2 installations) - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task9
            text: "Insert bolts to secure flanges (2 flanges) - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task10
            text: "Remove wellhead cover - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task11
            text: "Install wellhead gasket - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task12
            text: "Replace wellhead cover - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task13
            text: "Insert hot stab into wellhead port - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task14
            text: "Remove hot stab and return to surface - 5pts"
            worth: 5
        }
    }

    Label {
        id: points
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignBottom

        font.bold: true
        font.pixelSize: 20
        color: "white"
        text: "Pipeline Inspection & Repair: " + taskList.value + "pts"
    }
}
