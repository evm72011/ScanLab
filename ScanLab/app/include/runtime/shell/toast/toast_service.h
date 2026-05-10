#pragma once

#include <functional>
#include <string>
#include <vector>

class ToastService
{
public:
    enum class Icon
    {
        Info,
        Success,
        Warning,
        Error
    };

    struct Toast
    {
        std::string title;
        std::string text;
        Icon icon = Icon::Info;
        int durationMs = 3000;
    };

    using Handler = std::function<void(const Toast&)>;

    void show(std::string title, std::string text, Icon icon, int durationMs);
    void showInfo(std::string title, std::string text);
    void showWarning(std::string title, std::string text);
    void showError(std::string title, std::string text);

    void subscribe(Handler handler);

private:
    std::vector<Handler> handlers_;
};