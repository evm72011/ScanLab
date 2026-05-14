#include "ui/shell/toast/toast_facade.h"

ToastFacade::ToastFacade(ToastService& service, QObject* parent)
    : QObject(parent)
    , service_(service)
{
    service_.subscribe([this](const ToastService::Toast& toast) {
        auto iconSource = getIconSource(toast.icon);
        emit toastRequested(toast.title, toast.text, iconSource, toast.durationMs);
    });
}
