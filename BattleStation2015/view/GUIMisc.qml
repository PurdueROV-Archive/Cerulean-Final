import QtQuick 2.4

ROVBox {
    id: sysStatus
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    clip: true

    height: (parent.height/2) - 10

    ROVTitle {
        id: sysStatusTitle
        text: "Calculation/Misc"
    }
}
