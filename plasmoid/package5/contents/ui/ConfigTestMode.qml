import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.5

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kquickcontrolsaddons 2.0 as KQuickAddons
import org.kde.kirigami 2.20 as Kirigami
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.components 3.0 as PlasmaComponents3

ColumnLayout {
    property alias cfg_testModeEnabled: testModeEnabledCheckbox.checked
    property alias cfg_testModeApiUrl: testModeApiUrlTextField.text

    Kirigami.FormLayout {
        CheckBox {
            id: testModeEnabledCheckbox
            text: qsTr("Use custom API server URL for testing")
        }

        PlasmaComponents3.Label {
            wrapMode: Text.WordWrap
            Layout.preferredWidth: parent.parent.width
            text: qsTr("WARNING: While test mode is enabled, the plasmoid will not connect to real trains.")
            font.bold: true
        }

        Kirigami.ActionTextField {
            id: testModeApiUrlTextField
            Layout.preferredWidth: parent.parent.width
            Kirigami.FormData.label: qsTr("Custom API base url:")
            placeholderText: "http://localhost:9000/api1/rs"
        }

        Label {
            wrapMode: Text.WordWrap
            text: qsTr("You can <a href=\"https://raw.githubusercontent.com/ThePBone/onboard-plasmoid/master/misc/iceportal_api_snapshot.zip\">download an old ICE Portal API dump</a> and use the provided 'run_server.sh' script to setup a simple fake API for testing.")
            onLinkActivated: Qt.openUrlExternally(link)
            Layout.preferredWidth: parent.parent.width
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                acceptedButtons: Qt.NoButton // Don't eat the mouse clicks
                cursorShape: Qt.PointingHandCursor
            }
        }
    }


    Item {
        Layout.fillHeight: true
    }
}
