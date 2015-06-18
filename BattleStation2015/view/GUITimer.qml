import QtQuick 2.4

ROVBox {
    property real startTime: 0
    property real delta: 0

    //Timer Title
    ROVTitle {
        id: timerTitle
        text: "Timer"
    }

    //Timer
    Timer {
        id: timerTrigger
        interval:500
        running:false
        repeat: true
        onTriggered: {
            var tempTime = Math.floor(((new Date).getTime() - startTime)/1000);
            var secs = (tempTime % 60);
            var mins = Math.floor(tempTime/60);

            secs = (secs < 10) ? ("0" + secs) : secs;
            mins = (mins < 10) ? ("0" + mins) : mins;

            timer.text =  mins + ":" + secs;

            if (mins >= 10) {
                timer.color = "orange";
            }
            if (mins >= 13) {
                timer.color = "red"
            }

        }
    }

    //Holder for buttons and text
    Item {
        id: timerRow
        anchors.top: timerTitle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10


        //Start button
        ROVButton {
            id: startBtn
            height: 70
            width: 150
            text: qsTr("START")
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            enabled: true
            MouseArea {
                id: startButton
                height: startBtn.height
                width: startBtn.width
                anchors.fill: parent
                onClicked: {
                    if (timerTrigger.running) {
                        timerTrigger.stop();
                        resetBtn.enabled = true;
                        delta = (new Date).getTime() - startTime;
                        startBtn.text = "RESUME";
                    } else {
                        timerTrigger.running = true;
                        resetBtn.enabled = false;
                        startBtn.text = "PAUSE";
                        if (startTime == 0) {
                            startTime = (new Date).getTime();
                        } else {
                            startTime = (new Date).getTime() - delta;
                        }
                    }
                }
            }
        }

        //Stop button
        ROVButton {
            id: resetBtn
            height: 70
            width: 150
            text: qsTr("RESET")
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            enabled: false
            MouseArea {
                id: resetButton
                height: resetBtn.height
                width: resetBtn.width
                anchors.fill: parent
                onClicked: {
                    if (!timerTrigger.running) {
                        timerTrigger.running = false;
                        resetBtn.enabled = false;
                        startBtn.text = "START";
                        timer.text = "00:00";
                        timer.color = mainColor;
                        startTime = 0;
                    }
                }
            }
        }

        //Timer text
        Text {
            id: timer
            y: 0
            width: 171
            height: 70
            text: "00:00"
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 0

            color: mainColor
            font.family: "Arial"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 56
        }
    }
}

