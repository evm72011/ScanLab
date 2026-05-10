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
        ShellServices& shellServices
        ,QObject* parent = nullptr);

public slots:
    void refreshConfigFiles();
    void loadConfigFile(const QString& fileName);

signals:
    void configFilesUpdated(QStringList files);
    void configFilesErrorCode(QString errorCode);

    void configFileLoaded(QString fileName);
    void configFileLoadFailed(QString fileName, QString errorCode);

private:
    ToastService& toastService_;
    ConfigFileService service_;
};