#include "runtime/shell/shell_services.h"

ShellServices::ShellServices() = default;

ToastService& ShellServices::toastService()
{
    return toastService_;
}
