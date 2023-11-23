# onboard-plasmoid

Displays telemetry data about your current train trip in a plasmoid, if you are connected to a supported WIFI hotspot on the train.


In the panel:

![screenshot-panel](https://github.com/ThePBone/onboard-plasmoid/blob/master/screenshot/Screenshot_Panel2.png)

On the desktop:

![screenshot-desktop](https://github.com/ThePBone/onboard-plasmoid/blob/master/screenshot/Screenshot_DesktopHover1.png)

## Supported providers

* WIFIonICE: IC/EC/ICE trains (Germany)

## Installation

### Arch Linux
Install [onboard-plasmoid-git](https://aur.archlinux.org/packages/onboard-plasmoid-git) from the AUR:
```
yay -S onboard-plasmoid-git
```

### Compile from sources
Install dependencies

* Qt
* NetworkManagerQt
* extra-cmake-modules
* plasma-workspace
* [c++utilities](https://github.com/Martchus/cpp-utilities)
* [qtutilities](https://github.com/Martchus/qtutilities)

Configure cmake project

```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. 
```

Compile sources

```
make
```

Install CLI and plasmoid

```
sudo make install
```

If you are upgrading to a newer version and have already added the plasmoid to your panel or desktop, you also need to restart Plasma:

```
kquitapp5 plasmashell; kstart5 plasmashell
```

## Usage

### Plasmoid

Right-click your panel or desktop, select 'Add widgets' and choose the plasmoid called 'Onboard' from the list. 

This plasmoid has a dynamic width and **should be placed in front of a spacer** if used in the panel. It will turn invisible and shrink in size a bit if you are not connected to a supported WIFI hotspot.  

Please check this screenshot for a recommended layout choice:
[![screenshot-full](https://github.com/ThePBone/onboard-plasmoid/blob/master/screenshot/Screenshot_Full1.png)](https://raw.githubusercontent.com/ThePBone/onboard-plasmoid/master/screenshot/Screenshot_Full1.png)
My panel uses the following widgets: `Application Launcher | Virtual desktop pager | Onboard plasmoid | SPACER | Task manager | SPACER | System tray | Clock`

I'm using the [Papirus icon theme](https://github.com/PapirusDevelopmentTeam/papirus-icon-theme) which has better looking arrows than the default one.

The plasmoid is configurable and also supports a test mode for local testing with saved API responses:
![screenshot-config](https://github.com/ThePBone/onboard-plasmoid/blob/master/screenshot/Screenshot_Config1.png)

### CLI

The plasmoid is bundled with a simple CLI application that can be used to monitor the train status within the terminal.

```
onboard -tn
```

```
Distance since start:     233.2km
Distance since last stop: 19.2km
Total distance:           467.8km
Line number:              ICE 1556
Destination:              Wiesbaden Hbf (8000250)

Next station:             Eisenach (8010097)
Remaining distance:       27.0km
Arriving on platform:     5
Scheduled arrival time:   02 Sep 2023 16:46:00 +0200
Actual arrival time:      02 Sep 2023 16:47:00 +0200
Scheduled departure time: 02 Sep 2023 16:48:00 +0200
Actual departure time:    02 Sep 2023 16:49:00 +0200
```

## Credits

* CMake project structure based on https://github.com/Martchus/syncthingtray
