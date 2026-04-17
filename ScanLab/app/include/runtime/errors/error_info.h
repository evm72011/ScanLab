#pragma once

#include <QString>

struct ErrorInfo
{
    QString technicalCode;
    const char* textKey;
    QString fallbackText;
};
