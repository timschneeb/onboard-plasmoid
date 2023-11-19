import QtQuick 2.2
import QtQuick.Layouts 1.1
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kquickcontrolsaddons 2.0

Item {
    id: onboardApplet

    Plasmoid.preferredRepresentation: Plasmoid.compactRepresentation

    Plasmoid.compactRepresentation: CompactRepresentation {
        onWidthChanged: {
            onboardApplet.Layout.minimumSize = width
            onboardApplet.Layout.maximumSize = width
        }
    }

    // Plasmoid.fullRepresentation: FullRepresentation {}

    Plasmoid.toolTipMainText: plasmoid.nativeInterface.tooltipText
    Plasmoid.toolTipSubText: plasmoid.nativeInterface.secondaryTooltipText
    Plasmoid.toolTipItem: ToolTipView {}

    Plasmoid.hideOnWindowDeactivate: true

    function action_configure() {
        // plasmoid.nativeInterface.showSettings()
    }

    Component.onCompleted: {
        plasmoid.nativeInterface.initEngine(this)

        // plasmoid.removeAction("configure")
        // plasmoid.setAction("configure", qsTr("Settings"), "configure")
        // plasmoid.action("showErrors").visible = Qt.binding(() => { return plasmoid.nativeInterface.hasInternalErrors })
    }
}
