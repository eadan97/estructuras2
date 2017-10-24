import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import progra2 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    BackEnd{
        id: backend
    }
    StartDialogForm{
        anchors.fill: parent
    }
    FileDialog{
        id: fileDNombres
            title: "Elija el archivo que contiene los nombres"
            folder: shortcuts.home
            nameFilters: [ "Archivos de texto (*.txt)", "Todos los archivos (*)" ]
            onAccepted: {
                console.log("You chose: " + fileDNombres.fileUrls)
                backend.fileNombres=fileDNombres.fileUrl
            }
            onRejected: {
                console.log("Canceled")
                Qt.quit()
            }

    }

}
