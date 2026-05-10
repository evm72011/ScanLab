#pragma once

#include "runtime/shell/toast/toast_service.h"

#include <QObject>
#include <QString>

class ToastFacade : public QObject
{
    Q_OBJECT

public:
    enum class Icon
    {
        Info,
        Success,
        Warning,
        Error
    };

    Q_ENUM(Icon)

    explicit ToastFacade(QObject* parent = nullptr);
    ToastService& toastService();

signals:
    void toastRequested(QString title, QString text, QString iconSource, int durationMs);

private:
    static QString toFacadeIcon(ToastService::Icon icon);

    ToastService service_;
};