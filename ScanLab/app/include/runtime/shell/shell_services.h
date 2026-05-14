#pragma once

#include "runtime/shell/dialogs/message_service.h"
#include "runtime/shell/toast/toast_service.h"

class ShellServices
{
public:
    ShellServices();

    MessageService& messageService();
    ToastService& toastService();

private:
    MessageService messageService_;
    ToastService toastService_;
};
