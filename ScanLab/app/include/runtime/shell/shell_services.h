#pragma once

#include "runtime/shell/toast/toast_service.h"

class ShellServices
{
public:
    ShellServices();

    ToastService& toastService();

private:
    ToastService toastService_;
};
