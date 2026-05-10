#include "ui/shell/shell_facade.h"

ShellFacade::ShellFacade(QObject* parent) : QObject(parent)
{
}

ToastFacade* ShellFacade::toastFacade()
{
    return &toastFacade_;
}

ShellServices& ShellFacade::shellServices() {
    return shellServices_;
}