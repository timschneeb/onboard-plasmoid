#ifndef UTILS_H
#define UTILS_H

#include <QString>

#include <libonboard/Log.h>

namespace utils
{
    /**
     * @brief parseDelayTime
     * @param input: String of format '+10', '+3', or empty string
     * @return Delay time in minutes
     */
    int parseDelayTime(const QString& input);
};

#endif // UTILS_H
