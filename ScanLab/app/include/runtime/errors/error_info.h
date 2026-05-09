#pragma once

#include <QCoreApplication>
#include <QString>

struct ErrorInfo
{
    QString technicalCode;
    const char* textKey = nullptr;

    QString message() const
    {
        if (textKey != nullptr)
        {
            return QCoreApplication::translate("Errors", textKey);
        }

        return {};
    }
};
