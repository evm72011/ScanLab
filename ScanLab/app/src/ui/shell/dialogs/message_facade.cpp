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
            const auto title = QString::fromStdString(message.title);
            const auto shortText =  QString::fromStdString(message.shortText);
            const auto detailsText = QString::fromStdString(message.detailsText);
            const auto errorCode = QString::fromStdString(message.errorCode);
            const auto iconSource = getIconSource(message.icon);

            emit messageRequested(title, shortText, detailsText, errorCode, iconSource);
        }
    );
}
