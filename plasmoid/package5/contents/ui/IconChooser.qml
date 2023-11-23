import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.5

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.kquickcontrolsaddons 2.0 as KQuickAddons
import org.kde.kirigami 2.20 as Kirigami

Button {
    id: iconButton

    property string label
    property string value
    property string defaultValue

    Kirigami.FormData.label: label
    implicitWidth: previewFrame.width + PlasmaCore.Units.smallSpacing * 2
    implicitHeight: previewFrame.height + PlasmaCore.Units.smallSpacing * 2
    hoverEnabled: true

    Accessible.role: Accessible.ButtonMenu

    ToolTip.delay: Kirigami.Units.toolTipDelay
    ToolTip.text: qsTr("Icon name is \"%1\"").arg(value)
    ToolTip.visible: iconButton.hovered && value.length > 0

    KQuickAddons.IconDialog {
        id: iconDialog
        onIconNameChanged: value = iconName || defaultValue
    }

    onPressed: iconMenu.opened ? iconMenu.close() : iconMenu.open()

    PlasmaCore.FrameSvgItem {
        id: previewFrame
        anchors.centerIn: parent
        width: PlasmaCore.Units.iconSizes.large + fixedMargins.left + fixedMargins.right
        height: PlasmaCore.Units.iconSizes.large + fixedMargins.top + fixedMargins.bottom

        PlasmaCore.IconItem {
            anchors.centerIn: parent
            width: PlasmaCore.Units.iconSizes.large
            height: width
            source: (value === "")
                    ? defaultValue : value;
        }
    }

    Menu {
        id: iconMenu

        // Appear below the button
        y: +parent.height

        MenuItem {
            text: qsTr("Choose…")
            icon.name: "document-open-folder"
            onClicked: iconDialog.open()
        }
        MenuItem {
            text: qsTr("Reset icon to default")
            icon.name: "edit-clear"
            enabled: value !== defaultValue
            onClicked: value = defaultValue
        }
    }
}
