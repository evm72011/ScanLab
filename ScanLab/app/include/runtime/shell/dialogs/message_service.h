#pragma once

#include <QString>
#include <functional>
#include <vector>

#include "runtime/errors/error_info.h"
#include "runtime/shell/icon.h"

class MessageService
{
public:
    struct Message
    {
        QString title;
        QString shortText;
        QString detailsText;
        QString errorCode;
        Icon icon = Icon::Info;
    };

    using Handler = std::function<void(const Message&)>;

    void show(QString title, QString shortText, QString detailsText, QString errorCode, Icon icon);

    void showInfo(QString title,
        QString shortText,
        QString detailsText = {},
        QString errorCode = {});

    void showSuccess(QString title,
        QString shortText,
        QString detailsText = {},
        QString errorCode = {});

    void showWarning(QString title,
        QString shortText,
        QString detailsText = {},
        QString errorCode = {});

    void showError(QString title,
        QString shortText,
        QString detailsText = {},
        QString errorCode = {});

    void showError(QString title, QString shortText, const ErrorInfo& errorInfo);

    void subscribe(Handler handler);

private:
    std::vector<Handler> handlers_;
};