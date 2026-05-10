#include "ui/shell/toast/toast_facade.h"

ToastFacade::ToastFacade(ToastService& service, QObject* parent)
    : QObject(parent)
    , service_(service)
{
    service_.subscribe([this](const ToastService::Toast& toast) {
        emit toastRequested(
            QString::fromStdString(toast.title),
            QString::fromStdString(toast.text),
            toFacadeIcon(toast.icon),
            toast.durationMs
            );
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