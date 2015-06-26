import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

import "view" as ROVView

Window {
    property string rovName: "Cerulean"
    property string cerulean: "#6D9BC3"
    property string teal:     "#00BCD4"
    property string amber:    "#FFC107"
    property string mainColor: teal
    property string mainAccent: amber

    id: mainWindow
    visible: true
    width: 1920
    height: 1010
    visibility: "Maximized"
    color: "#151515"
    title: "Purdue IEEE | ROV " + rovName
    objectName: "mainWindow"

    FontLoader {
        id: roboto
        source: "qrc:/view/Roboto.ttf"
    }

    FontLoader {
        id: robotoBold
        source: "qrc:/view/Roboto-Bold.ttf"
    }

    Rectangle {
        id: actionBar
        height: 60
        width: mainWindow.width
        color: mainColor

        Text {
            x: 20
            height: actionBar.height
            font.family: roboto.name
            font.pixelSize: 30

            color: "white"
            verticalAlignment: Text.AlignVCenter

            text: "International Big BlueBotix's BattleStation | ROV Cerulean"
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: actionBar.bottom
            height: 20
            gradient: Gradient {
                 GradientStop { position: 0.0; color: "#33000000" }
                 GradientStop { position: 1.0; color: "#00000000" }
             }
        }
    }

    Item {
        objectName: "mainGrid"
        id: mainGrid

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: actionBar.bottom

        anchors.margins: 10
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        clip: true
        transformOrigin: Item.TopLeft






//        //Titles
//        Row {
//            id: titleRow
//            width: mainGrid.width - 40
//            height: 60
//            anchors.horizontalCenterOffset: 0
//            anchors.horizontalCenter: parent.horizontalCenter

//            //Purdue IEEE
//            Text {
//                id: purdueTitle
//                width: parent.width/3
//                height: titleRow.height
//                color: mainColor
//                text: "PURDUE IEEE IBBB"
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignLeft
//                font.bold: true
//                font.family: robotoBold.name
//                font.pixelSize: 28
//            }

//            //Battlestation Title
//            Text {
//                id: mainTitle
//                width: parent.width/3
//                height: titleRow.height
//                color: mainColor
//                text: "BATTLESTATION"
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//                font.bold: true
//                font.family: robotoBold.name
//                font.pixelSize: 46
//            }

//            //ROV Name
//            Text {
//                id: rovTitle
//                width: parent.width/3
//                height: titleRow.height
//                color: mainColor
//                text: "ROV " + rovName
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignRight
//                font.italic: true
//                font.bold: true
//                font.family: robotoBold.name
//                font.pixelSize: 28
//            }
//        }


        //Left Column
        Column {
            id: leftColumn

            width: mainGrid.width/3
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.left: mainGrid.left
            anchors.leftMargin: 0

            //Timer Container
            ROVView.GUITimer {}

            //Mission Tasks
            ROVView.GUIMissionTasks {}
        }

        //Center Column
        Column {
            id: centerColumn

            width: mainGrid.width/3
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            //System View
            ROVView.GUISystemStatus {}

            //Thruster Status
            ROVView.GUIThrusters {}
        }

        //Right Column
        Column {
            id: rightColumn

            width: mainGrid.width/3
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.right: mainGrid.right
            anchors.rightMargin: 0

            //System Details
            ROVView.GUIMisc {}

            //Config Details
            ROVView.GUIConfiguration {}
        }
    }
}
