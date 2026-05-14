#pragma once

#include "runtime/shell/toast/toast_service.h"

#include <QObject>
#include <QString>

class ToastFacade : public QObject
{
    Q_OBJECT

public:

    explicit ToastFacade(ToastService& service, QObject* parent = nullptr);

signals:
    void toastRequested(QString title, QString text, QString iconSource, int durationMs);

private:
    static QString toFacadeIcon(Icon icon);

    ToastService& service_;
};