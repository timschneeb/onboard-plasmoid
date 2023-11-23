cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)

# metadata
set(META_PROJECT_NAME onboard)
set(META_APP_NAME "Onboard CLI")
set(META_APP_DESCRIPTION "Command line app to interact with WIFIonICE train hotspots")
set(META_PROJECT_TYPE application)

# add project files
set(HEADER_FILES )
set(SRC_FILES main.cpp)

# find c++utilities
find_package(${PACKAGE_NAMESPACE_PREFIX}c++utilities${CONFIGURATION_PACKAGE_SUFFIX} 5.20.0 REQUIRED)
use_cpp_utilities()

# find qtutilities
find_package(${PACKAGE_NAMESPACE_PREFIX}qtutilities${CONFIGURATION_PACKAGE_SUFFIX_QTUTILITIES} 6.0.0 REQUIRED)
use_qt_utilities(ONLY_HEADERS VISIBILITY PUBLIC)

# find backend libraries
find_package(libonboard ${META_APP_VERSION} REQUIRED)
use_libonboard()

# include modules to apply configuration
include(BasicConfig)
include(QtConfig)
include(AppTarget)
include(ConfigHeader)
