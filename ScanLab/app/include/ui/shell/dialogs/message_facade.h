#pragma once

#include "runtime/shell/dialogs/message_service.h"

#include <QObject>
#include <QString>

class MessageFacade : public QObject
{
    Q_OBJECT

public:
    explicit MessageFacade(
        MessageService& service,
        QObject* parent = nullptr
        );

signals:
    void messageRequested(
        QString title,
        QString shortText,
        QString detailsText,
        QString errorCode,
        QString iconSource
        );

private:
    static QString toIconSource(MessageService::Icon icon);

    MessageService& service_;
};