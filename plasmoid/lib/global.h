// Created via CMake from template global.h.in
// WARNING! Any changes to this file will be overwritten by the next CMake run!

#ifndef ONBOARDPLASMOID_GLOBAL
#define ONBOARDPLASMOID_GLOBAL

#include <c++utilities/application/global.h>

#ifdef ONBOARDPLASMOID_STATIC
#define ONBOARDPLASMOID_EXPORT
#define ONBOARDPLASMOID_IMPORT
#else
#define ONBOARDPLASMOID_EXPORT CPP_UTILITIES_GENERIC_LIB_EXPORT
#define ONBOARDPLASMOID_IMPORT CPP_UTILITIES_GENERIC_LIB_IMPORT
#endif

/*!
 * \def ONBOARDPLASMOID_EXPORT
 * \brief Marks the symbol to be exported by the onboardplasmoid library.
 */

/*!
 * \def ONBOARDPLASMOID_IMPORT
 * \brief Marks the symbol to be imported from the onboardplasmoid library.
 */

#endif // ONBOARDPLASMOID_GLOBAL
