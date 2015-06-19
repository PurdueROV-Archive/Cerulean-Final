
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
            (task10.value) + (task11.value)
        }

        ROVMissionTask {
            id: task1
            text: "Test first anode - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task2
            text: "Test second anode - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task3
            text: "Test third anode - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task4
            text: "Test fourth anode - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task5
            text: "Measure wellhead height - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task6
            text: "Measure wellhead length - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task7
            text: "Calculate wellhead angle - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task8
            text: "Evaluate pipeline system oil flow - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task9
            text: "Open/Close all 6 valves - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task10
            text: "Move water through pipeway - 20pts"
            worth: 20
        }
        ROVMissionTask {
            id: task11
            text: "Determine average flow rate - 10pts"
            worth: 10
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
        text: "Oilfield Prod & Maintenance: " + taskList.value + "pts"
    }
}
