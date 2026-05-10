#include "ui/shell/toast/toast_facade.h"

ToastFacade::ToastFacade(ToastService& service, QObject* parent)
    : QObject(parent)
    , service_(service)
{
    service_.subscribe([this](const ToastService::Toast& toast) {
        auto title = QString::fromStdString(toast.title);
        auto text = QString::fromStdString(toast.text);
        auto icon = toFacadeIcon(toast.icon);
        emit toastRequested(title, text, icon, toast.durationMs);
    });
}

QString ToastFacade::toFacadeIcon(ToastService::Icon icon)
{
    switch (icon)
    {
    case ToastService::Icon::Info:
        return QString::fromStdString("qrc:/icons/information.svg");

    case ToastService::Icon::Success:
        return QString::fromStdString("qrc:/icons/information.svg");

    case ToastService::Icon::Warning:
        return QString::fromStdString("qrc:/icons/warning.svg");

    case ToastService::Icon::Error:
        return QString::fromStdString("qrc:/icons/error.svg");
    }

    return QString::fromStdString("qrc:/icons/information.svg");
}
