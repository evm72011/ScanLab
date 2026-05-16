#pragma once

#include "runtime/config/config_file_service.h"
#include "runtime/shell/shell_services.h"

#include <QObject>
#include <QString>
#include <QStringList>

class DeviceContext;

class ConfigFileWorker : public QObject
{
    Q_OBJECT

public:
    explicit ConfigFileWorker(DeviceContext& context,
        ShellServices& shellServices,
        QObject* parent = nullptr);

public slots:
    void loadConfigFile(const QString& fileName);
    void saveConfigFile(const QString& fileName);

signals:
    void loadCompleted();
    void saveCompleted();

private:
    MessageService& messageService_;
    ToastService& toastService_;
    ConfigFileService service_;
};