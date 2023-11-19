// Created via CMake from template global.h.in
// WARNING! Any changes to this file will be overwritten by the next CMake run!

#ifndef LIB_ONBOARD_GLOBAL
#define LIB_ONBOARD_GLOBAL

#include <c++utilities/application/global.h>

#ifdef LIB_ONBOARD_STATIC
#define LIB_ONBOARD_EXPORT
#define LIB_ONBOARD_IMPORT
#else
#define LIB_ONBOARD_EXPORT CPP_UTILITIES_GENERIC_LIB_EXPORT
#define LIB_ONBOARD_IMPORT CPP_UTILITIES_GENERIC_LIB_IMPORT
#endif

/*!
 * \def LIB_ONBOARD_EXPORT
 * \brief Marks the symbol to be exported by the libonboard library.
 */

/*!
 * \def LIB_ONBOARD_IMPORT
 * \brief Marks the symbol to be imported from the libonboard library.
 */

#endif // LIB_ONBOARD_GLOBAL
