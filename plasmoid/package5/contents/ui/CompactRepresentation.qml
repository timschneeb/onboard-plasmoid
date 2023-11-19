import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3

MouseArea {
    id: mouseArea
    hoverEnabled: true
    // TODO onClicked: plasmoid.expanded = !plasmoid.expanded

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 8
        anchors.rightMargin: 4
        anchors.leftMargin: 4
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        onImplicitWidthChanged: {
            var w = rowLayout.implicitWidth + units.gridUnit * 1
            mouseArea.Layout.minimumWidth = w
            mouseArea.Layout.maximumWidth = w
        }

        PlasmaCore.IconItem {
            id: icon
            source: plasmoid.nativeInterface.statusIcon
            active: parent.parent.containsMouse

            implicitWidth: 32
            implicitHeight: 32
        }

        ColumnLayout {
            id: column
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 0

            PlasmaComponents3.Label {
                id: topLabel
                height: 17
                text: plasmoid.nativeInterface.statusText
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pointSize: 9
                font.bold: true
            }

            PlasmaComponents3.Label {
                height: 17
                text: plasmoid.nativeInterface.secondaryStatusText
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pointSize: 9
            }
        }
    }
}
