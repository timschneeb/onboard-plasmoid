import QtQuick 2.0

import org.kde.plasma.configuration 2.0 as PlasmaConfig

PlasmaConfig.ConfigModel {
    PlasmaConfig.ConfigCategory {
        name: qsTr("General")
        icon: "preferences-desktop-plasma"
        source: "ConfigGeneral.qml"
    }

    PlasmaConfig.ConfigCategory {
        name: qsTr("Test mode")
        icon: "preferences-other"
        source: "ConfigTestMode.qml"
    }
}
