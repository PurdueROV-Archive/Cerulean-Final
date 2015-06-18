import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVBox {
    id: sysViewArea
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 10
    clip: true

    height: (parent.height/2) - 10

    ROVTitle {
        id: sysTitle
        text: "System Status"
    }
}