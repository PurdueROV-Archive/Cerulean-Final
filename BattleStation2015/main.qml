import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

import "view" as ROVView

Window {
    property string rovName: "Cerulean"
    property string mainColor: "#6D9BC3"
    visible: true
    width: 1920
    height: 1010
    visibility: "Maximized"
    color: "#111111"
    title: "Purdue IEEE | ROV " + rovName
    objectName: "mainWindow"


    Item {
        objectName: "mainGrid"
        id: mainGrid
        width: parent.height
        height: parent.width
        clip: true
        transformOrigin: Item.TopLeft
        anchors.margins: 10
        anchors.bottomMargin: 20
        anchors.fill: parent

        //Titles
        Row {
            id: titleRow
            width: mainGrid.width - 40
            height: 60
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            //Purdue IEEE
            Text {
                id: purdueTitle
                width: parent.width/3
                height: titleRow.height
                color: mainColor
                text: "PURDUE IEEE IBBB"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 28
            }

            //Battlestation Title
            Text {
                id: mainTitle
                width: parent.width/3
                height: titleRow.height
                color: mainColor
                text: "BATTLESTATION"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 46
            }

            //ROV Name
            Text {
                id: rovTitle
                width: parent.width/3
                height: titleRow.height
                color: mainColor
                text: "ROV" + rovName
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.italic: true
                font.bold: true
                font.family: "Arial"
                font.pixelSize: 28
            }
        }


        //Left Column
        ROVView.LeftColumn{}

        //Center Column
        ROVView.CenterColumn{}

        //Right Column
        ROVView.RightColumn{}
    }
}
