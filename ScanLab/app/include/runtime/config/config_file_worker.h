#pragma once

#include "runtime/config/config_file_service.h"

#include <QObject>
#include <QString>
#include <QStringList>

class DeviceContext;

class ConfigFileWorker : public QObject {
    Q_OBJECT

public:
    explicit ConfigFileWorker(DeviceContext& context, QObject* parent = nullptr);

public slots:
    void refreshConfigFiles();
    void loadConfigFile(QString fileName);

signals:
    void configFilesUpdated(QStringList files);
    void configFilesErrorCode(QString errorCode);

    void configFileLoaded(QString fileName);
    void configFileLoadFailed(QString fileName, QString errorCode);

private:
    ConfigFileService service_;
};