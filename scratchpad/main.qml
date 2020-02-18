import QtQuick 2.11
import QtQuick.Window 2.4
 Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Scratchpad")
    color: "#ffffff"
 Text {
        id: message
        anchors.centerIn: parent
        font.pixelSize: 44
        text: qsTr("Welcome to QT GUI")
        color: "#008000"
    }
}
