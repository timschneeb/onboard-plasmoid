cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)

# define metadata
set(META_PROJECT_NAME onboard)
set(META_APP_AUTHOR "Tim Schneeberger")
set(META_APP_AUTHOR_MAIL "contact@timschneeberger.me")
set(META_APP_URL "https://github.com/thepbone/onboard-plasmoid")
set(META_APP_URL_RAW "https://raw.githubusercontent.com/thepbone/onboard-plasmoid/master")
set(META_APP_DESCRIPTION "WIFIonICE train tracking integration for German ICE trains")
set(META_APP_CATEGORIES "Utility;Network;Travel")
set(META_PROJECT_LICENSE "GPL-3.0")
set(META_GUI_OPTIONAL false)

set(META_VERSION_MAJOR 1)
set(META_VERSION_MINOR 0)
set(META_VERSION_PATCH 0)
set(META_RELEASE_DATE "2023-11-19")
set(META_SOVERSION 1)

set(META_NO_TIDY 1)

project(${META_PROJECT_NAME})

set(PLASMOID_DISABLED_BY_DEFAULT OFF)

# determine Qt and KDE Frameworks version bases on the package prefix
set(QT_PACKAGE_PREFIX
    "Qt5"
    CACHE STRING "specifies the prefix for Qt packages")
set(KF_PACKAGE_PREFIX
    "KF5"
    CACHE STRING "specifies the prefix for KDE Frameworks packages")
set(QT_MAJOR_VERSION 5)
if (QT_PACKAGE_PREFIX MATCHES ".*Qt([0-9]+).*")
    set(QT_MAJOR_VERSION "${CMAKE_MATCH_1}")
endif ()
set(KF_MAJOR_VERSION 5)
if (KF_PACKAGE_PREFIX MATCHES ".*KF([0-9]+).*")
    set(KF_MAJOR_VERSION "${CMAKE_MATCH_1}")
endif ()


# add subdirectories
add_subdirectory(qtpromise)
add_subdirectory(libonboard)
add_subdirectory(cli)
add_subdirectory(plasmoid)
