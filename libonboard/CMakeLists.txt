cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)

# metadata
set(META_PROJECT_NAME libonboard)
set(META_PROJECT_TYPE library)
set(META_APP_NAME "libonboard")
set(META_APP_DESCRIPTION "Library for communicating with onboard train WIFI hotspots with local APIs")
set(META_PROJECT_VARNAME_UPPER LIB_ONBOARD)
set(META_PUBLIC_QT_MODULES Gui Widgets Network)

# TODO: remove
add_definitions(
#    -DUSE_LOCAL_SERVER
)


# add project files
set(HEADER_FILES
    Log.h
    Onboard.h
    model/IDeserializable.h
    model/Connectivity.h
    model/CurrentTrip.h
    model/DelayReason.h
    model/Station.h
    model/Status.h
    model/Stop.h
    model/StopInfo.h
    model/StopTimetable.h
    model/Track.h
    model/TripStopInfo.h
    model/Trip.h
    network/HttpException.h
    network/OnboardApiClient.h
)
set(SRC_FILES
    Log.cpp
    Onboard.cpp
    model/IDeserializable.cpp
    network/HttpException.cpp
    network/OnboardApiClient.cpp
)

set(TS_FILES translations/${META_PROJECT_NAME}_de_DE.ts translations/${META_PROJECT_NAME}_en_US.ts)

# find c++utilities
find_package(${PACKAGE_NAMESPACE_PREFIX}c++utilities${CONFIGURATION_PACKAGE_SUFFIX} 5.0.0 REQUIRED)
use_cpp_utilities()

# find qtutilities (only CMake modules used)
find_package(${PACKAGE_NAMESPACE_PREFIX}qtutilities${CONFIGURATION_PACKAGE_SUFFIX_QTUTILITIES} 6.3.0 REQUIRED)
use_qt_utilities()

find_package(qtpromise ${META_APP_VERSION} REQUIRED)
use_qtpromise()

find_package(${KF_PACKAGE_PREFIX}NetworkManagerQt REQUIRED)
list(APPEND ADDITIONAL_KF_MODULES NetworkManagerQt)

# link also explicitly against the following Qt modules
list(APPEND ADDITIONAL_QT_MODULES Network Gui Widgets Svg)

# include modules to apply configuration
include(BasicConfig)
include(QtConfig)
include(LibraryTarget)
include(ConfigHeader)
