#pragma once

#include "runtime/shell/shell_services.h"
#include "ui/shell/toast/toast_facade.h"

#include <QObject>

class ShellFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ToastFacade* toastFacade READ toastFacade CONSTANT)

public:
    explicit ShellFacade(QObject* parent = nullptr);

    ToastFacade* toastFacade();
    ShellServices& shellServices();

private:
    ShellServices shellServices_;
    ToastFacade toastFacade_ { shellServices_.toastService(), this};
};
