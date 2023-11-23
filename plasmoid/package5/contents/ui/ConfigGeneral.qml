import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.5

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kquickcontrolsaddons 2.0 as KQuickAddons
import org.kde.kirigami 2.20 as Kirigami
import org.kde.plasma.extras 2.0 as PlasmaExtras


ColumnLayout {
    property string cfg_iconDisconnect: plasmoid.configuration.iconDisconnect
    property alias cfg_iconDisconnectShown : iconDisconnectShownCheckbox.checked
    property alias cfg_labelDisconnectShown: labelDisconnectShownCheckbox.checked

    Kirigami.FormLayout {
        Button {
            id: iconButton

            Kirigami.FormData.label: qsTr("Disconnection icon:")

            implicitWidth: previewFrame.width + PlasmaCore.Units.smallSpacing * 2
            implicitHeight: previewFrame.height + PlasmaCore.Units.smallSpacing * 2
            hoverEnabled: true

            Accessible.role: Accessible.ButtonMenu

            ToolTip.delay: Kirigami.Units.toolTipDelay
            ToolTip.text: qsTr("Icon name is \"%1\"", cfg_iconDisconnect)
            ToolTip.visible: iconButton.hovered && cfg_iconDisconnect.length > 0

            KQuickAddons.IconDialog {
                id: iconDialog
                onIconNameChanged: cfg_iconDisconnect = iconName || "network-offline-symbolic"
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
                    source: (cfg_iconDisconnect === "")
                            ? "network-offline-symbolic" : cfg_iconDisconnect;
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
                    enabled: cfg_iconDisconnect !== "network-offline-symbolic"
                    onClicked: cfg_iconDisconnect = "network-offline-symbolic"
                }
                MenuItem {
                    text: qsTr("Remove icon")
                    icon.name: "delete"
                    enabled: cfg_iconDisconnect !== ""
                    onClicked: cfg_iconDisconnect = ""
                }
            }
        }

        CheckBox {
            id: iconDisconnectShownCheckbox
            text: qsTr("Show disconnection icon when not connected to any trains")
        }

        CheckBox {
            id: labelDisconnectShownCheckbox
            text: qsTr("Show error label when not connected to any trains")
        }
    }


    Item {
        Layout.fillHeight: true
    }
}
