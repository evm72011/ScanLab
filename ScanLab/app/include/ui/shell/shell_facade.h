#pragma once

#include "ui/shell/toast/toast_facade.h"

#include <QObject>

class ShellFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ToastFacade* toastFacade READ toastFacade CONSTANT)

public:
    explicit ShellFacade(QObject* parent = nullptr);

    ToastFacade* toastFacade();
    ToastService& toastService();

private:
    ToastFacade toastFacade_;
};