#include "ui/shell/toast/toast_facade.h"

ToastFacade::ToastFacade(QObject* parent) : QObject(parent)
{
    service_.subscribe(
        [this](const ToastService::Toast& toast) {
            emit toastRequested(
                QString::fromStdString(toast.title),
                QString::fromStdString(toast.text),
                QString::fromStdString("qrc:/icons/information.svg"),
                //toFacadeIcon(toast.icon),
                toast.durationMs
                );
        }
        );
}

ToastService& ToastFacade::toastService() {
    return service_;
}

ToastFacade::Icon ToastFacade::toFacadeIcon(ToastService::Icon icon)
{
    switch (icon)
    {
    case ToastService::Icon::Info:
        return Icon::Info;

    case ToastService::Icon::Success:
        return Icon::Success;

    case ToastService::Icon::Warning:
        return Icon::Warning;

    case ToastService::Icon::Error:
        return Icon::Error;
    }

    return Icon::Info;
}