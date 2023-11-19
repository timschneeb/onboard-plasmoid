#include "Utils.h"

namespace utils
{

    int parseDelayTime(const QString &input) {
        // Empty input: +0min
        if(input.length() < 1)
            return 0;

        // Filter out digits
        QString stripped;
        for (const QChar c : qAsConst(input)) {
            if (c.isDigit()) {
                stripped.append(c);
            }
        }
        // Convert to int
        bool ok = false;
        int result = stripped.toInt(&ok);
        if(!ok) {
            Log::error("Failed to convert stripped '" + input + "' to int");
            return 0;
        }
        return result;
    }

};
