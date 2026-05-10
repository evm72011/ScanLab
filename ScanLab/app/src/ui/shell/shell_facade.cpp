#include "ui/shell/shell_facade.h"

ShellFacade::ShellFacade(QObject* parent)
    : QObject(parent)
    , toastFacade_(this)
{
}

ToastFacade* ShellFacade::toastFacade()
{
    return &toastFacade_;
}

ToastService& ShellFacade::toastService()
{
    return toastFacade_.toastService();
}
