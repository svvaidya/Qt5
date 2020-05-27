import QtQuick 2.11
import QtQuick.Window 2.4
 Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Scratchpad Window")
    color: "#ffffff"
 Text {
        id: message
        anchors.centerIn: parent
        font.pixelSize: 44
        text: qsTr("Welcome to QT GUI Scratchpad project")
        color: "#008000"
    }
}
