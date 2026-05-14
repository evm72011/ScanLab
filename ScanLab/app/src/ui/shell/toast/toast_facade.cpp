#include "ui/shell/toast/toast_facade.h"

ToastFacade::ToastFacade(ToastService& service, QObject* parent)
    : QObject(parent)
    , service_(service)
{
    service_.subscribe([this](const ToastService::Toast& toast) {
        emit toastRequested(toast.title, toast.text, getIconSource(toast.icon), toast.durationMs);
    });
}
