#pragma once

#include <functional>
#include <string>
#include <vector>

class MessageService
{
public:
    enum class Icon
    {
        Info,
        Success,
        Warning,
        Error
    };

    struct Message
    {
        std::string title;
        std::string shortText;
        std::string detailsText;
        std::string errorCode;
        Icon icon = Icon::Info;
    };

    using Handler = std::function<void(const Message&)>;

    void show(
        std::string title,
        std::string shortText,
        std::string detailsText,
        std::string errorCode,
        Icon icon
        );

    void showInfo(
        std::string title,
        std::string shortText,
        std::string detailsText = {},
        std::string errorCode = {}
        );

    void showSuccess(
        std::string title,
        std::string shortText,
        std::string detailsText = {},
        std::string errorCode = {}
        );

    void showWarning(
        std::string title,
        std::string shortText,
        std::string detailsText = {},
        std::string errorCode = {}
        );

    void showError(
        std::string title,
        std::string shortText,
        std::string detailsText = {},
        std::string errorCode = {}
        );

    void subscribe(Handler handler);

private:
    std::vector<Handler> handlers_;
};