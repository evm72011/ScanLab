#include "ui/shell/dialogs/message_facade.h"

MessageFacade::MessageFacade(
    MessageService& service,
    QObject* parent
    )
    : QObject(parent)
    , service_(service)
{
    service_.subscribe(
        [this](const MessageService::Message& message) {
            emit messageRequested(
                QString::fromStdString(message.title),
                QString::fromStdString(message.shortText),
                QString::fromStdString(message.detailsText),
                QString::fromStdString(message.errorCode),
                toIconSource(message.icon)
                );
        }
        );
}

QString MessageFacade::toIconSource(MessageService::Icon icon)
{
    switch (icon)
    {
    case MessageService::Icon::Info:
        return "qrc:/icons/information.svg";

    case MessageService::Icon::Success:
        return "qrc:/icons/success.svg";

    case MessageService::Icon::Warning:
        return "qrc:/icons/warning.svg";

    case MessageService::Icon::Error:
        return "qrc:/icons/error.svg";
    }

    return "qrc:/icons/information.svg";
}