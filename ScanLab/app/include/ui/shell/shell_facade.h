#pragma once

#include "runtime/shell/shell_services.h"
#include "ui/shell/dialogs/message_facade.h"
#include "ui/shell/toast/toast_facade.h"

#include <QObject>

class ShellFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MessageFacade* messageFacade READ messageFacade CONSTANT)
    Q_PROPERTY(ToastFacade* toastFacade READ toastFacade CONSTANT)

public:
    explicit ShellFacade(QObject* parent = nullptr);

    ShellServices& shellServices();
    MessageFacade* messageFacade();
    ToastFacade* toastFacade();

private:
    ShellServices shellServices_;
    MessageFacade messageFacade_{ shellServices_.messageService(), this };
    ToastFacade toastFacade_{ shellServices_.toastService(), this };
};
