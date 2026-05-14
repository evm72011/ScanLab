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
                message.title,
                message.shortText,
                message.detailsText,
                message.errorCode,
                getIconSource(message.icon)
            );
        }
    );
}
