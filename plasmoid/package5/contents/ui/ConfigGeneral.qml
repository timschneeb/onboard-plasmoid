import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.5

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kquickcontrolsaddons 2.0 as KQuickAddons
import org.kde.kirigami 2.20 as Kirigami
import org.kde.plasma.extras 2.0 as PlasmaExtras


ColumnLayout {
    property string cfg_iconCurrentStop: plasmoid.configuration.iconCurrentStop
    property string cfg_iconNextStop: plasmoid.configuration.iconNextStop
    property string cfg_iconDisconnect: plasmoid.configuration.iconDisconnect
    property alias cfg_iconDisconnectShown : iconDisconnectShownCheckbox.checked
    property alias cfg_labelDisconnectShown: labelDisconnectShownCheckbox.checked

    Kirigami.FormLayout {
        IconChooser {
            id: iconCurrentStop
            label: qsTr("Current stop icon")
            value: cfg_iconCurrentStop
            defaultValue: plasmoid.nativeInterface.resolveFallbackIcon("go-right", "arrow-right")
            onValueChanged: cfg_iconCurrentStop = value
        }

        IconChooser {
            id: iconNextStop
            label: qsTr("Next stop icon")
            value: cfg_iconNextStop
            defaultValue: plasmoid.nativeInterface.resolveFallbackIcon("up", "arrow-up")
            onValueChanged: cfg_iconNextStop = value
        }

        IconChooser {
            id: iconDisconnect
            label: qsTr("Disconnect icon")
            value: cfg_iconDisconnect
            defaultValue: "network-offline-symbolic"
            onValueChanged: cfg_iconDisconnect = value
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
