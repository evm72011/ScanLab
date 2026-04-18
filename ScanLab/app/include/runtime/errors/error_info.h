#pragma once

#include <QString>
#include <QCoreApplication>

struct ErrorInfo
{
    QString technicalCode;
    const char* textKey = nullptr;

    QString message() const
    {
        if (textKey != nullptr) {
            return QCoreApplication::translate("Errors", textKey);
        }

        return {};
    }
};
