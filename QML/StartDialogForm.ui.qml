import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: rectangle
    width: 400
    height: 400
    color: "#ffffff"

    Grid {
        id: grid
        anchors.fill: parent
        spacing: 5
        rows: 6
        columns: 3

        Text {
            id: lblNombres
            text: qsTr("Archivo de nombres:")
            font.pixelSize: 12
        }

        TextInput {
            id: txtNombres
            width: 80
            height: 20
            text: qsTr("Seleccione un archivo...")
            font.pixelSize: 12
        }

        Button {
            id: btnNombres
            text: qsTr("Buscar")
        }

        Text {
            id: lblApellidos
            text: qsTr("Archivo de apellidos:")
            Layout.columnSpan: 1
            font.pixelSize: 12
        }

        TextInput {
            id: txtApellidos
            width: 80
            height: 20
            text: qsTr("Seleccione un archivo...")
            renderType: Text.QtRendering
            font.pixelSize: 12
        }

        Button {
            id: btnApellidos
            text: qsTr("Buscar")
        }

        Text {
            id: lblPaises
            text: qsTr("Archivo de paises:")
            font.pixelSize: 12
        }

        TextInput {
            id: txtPaises
            width: 80
            height: 20
            text: qsTr("Seleccione un archivo...")
            font.pixelSize: 12
        }

        Button {
            id: btnPaises
            text: qsTr("Buscar")
            Layout.columnSpan: 3
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        }

        Text {
            id: lblCreencias
            text: qsTr("Archivo de creencias:")
            font.pixelSize: 12
        }

        TextInput {
            id: txtCreencias
            width: 80
            height: 20
            text: qsTr("Seleccione un archivo...")
            font.pixelSize: 12
        }

        Button {
            id: btnCreencias
            text: qsTr("Buscar")
        }

        Text {
            id: lblProfesiones
            text: qsTr("Archivo de profesiones:")
            font.pixelSize: 12
        }

        TextInput {
            id: txtProfesiones
            width: 80
            height: 20
            text: qsTr("Seleccione un archivo...")
            font.pixelSize: 12
        }

        Button {
            id: btnProfesiones
            text: qsTr("Buscar")
        }

        Button {
            id: btnOk
            text: qsTr("Continuar")
        }
    }
}
