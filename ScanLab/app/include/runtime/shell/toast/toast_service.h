#pragma once

#include <QString>
#include <functional>
#include <vector>

#include "runtime/shell/icon.h"

class ToastService
{
public:
    struct Toast
    {
        QString title;
        QString text;
        Icon icon = Icon::Info;
        int durationMs = 3000;
    };

    using Handler = std::function<void(const Toast&)>;

    void show(QString title, QString text, Icon icon, int durationMs);
    void showInfo(QString title, QString text);
    void showWarning(QString title, QString text);
    void showError(QString title, QString text);

    void subscribe(Handler handler);

private:
    std::vector<Handler> handlers_;
};
