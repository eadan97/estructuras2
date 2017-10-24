import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    StartDialog{

    }

    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
        textEdit.onTextChanged: {
        console.log(qsTr('Text changed. Text: "'+textEdit.text+'"'))}
    }
}
