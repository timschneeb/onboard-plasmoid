# onboard-plasmoid

Displays telemetry data about your current train trip in a plasmoid, if you are connected to a supported WIFI hotspot on the train.

## Supported providers

* WIFIonICE: IC/EC/ICE trains (Germany)

## Installation

Install build dependencies

* Qt
* NetworkManagerQt
* extra-cmake-modules
* c++utilities
* qtutilities

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

This plasmoid has a dynamic width and should the placed in front of a spacer, if used in the panel. It will turn invisible and shrink its size, if you are not connected to a supported WIFI hotspot.  

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
