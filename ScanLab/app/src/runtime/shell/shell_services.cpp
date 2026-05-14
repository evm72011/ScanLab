#include "runtime/shell/shell_services.h"

ShellServices::ShellServices() = default;

MessageService& ShellServices::messageService()
{
    return messageService_;
}

ToastService& ShellServices::toastService()
{
    return toastService_;
}
