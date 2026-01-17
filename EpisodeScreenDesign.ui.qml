import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    width: 1024
    height: 768

    property alias episodeIdField: episodeIdField
    property alias confirmButton: confirmButton
    property alias charactersList: charactersList

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 32

        TextField {
            id: episodeIdField

            placeholderText: qsTr("Put our episode ID")
            Layout.preferredHeight: 50
            Layout.fillWidth: true
        }

        Button {
            id: confirmButton

            Layout.preferredHeight: 50
            Layout.fillWidth: true

            text: qsTr("Confirm")
        }

        ListView {
            id: charactersList

            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            spacing: 12

            delegate: Rectangle {
                width: ListView.view.width
                height: 50
                color: Qt.rgba(Math.random(255), Math.random(255),
                               Math.random(255), 1)

                Label {
                    font.pixelSize: 16
                    anchors.centerIn: parent
                    text: modelData
                }
            }
        }
    }
}
