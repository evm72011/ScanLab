#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QThread>

#include "ui/shell/shell_facade.h"

class DeviceContext;
class ConfigFileWorker;

class ConfigFileFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList availableConfigFiles READ availableConfigFiles NOTIFY
            availableConfigFilesChanged)

    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)

    Q_PROPERTY(QString errorCode READ errorCode NOTIFY errorCodeChanged)

    Q_PROPERTY(QString selectedConfigFile READ selectedConfigFile WRITE setSelectedConfigFile NOTIFY
            selectedConfigFileChanged)

public:
    explicit ConfigFileFacade(DeviceContext& context,
        ShellFacade& shellFacade,
        QObject* parent = nullptr);
    ~ConfigFileFacade() override;

    QStringList availableConfigFiles() const;
    QString selectedConfigFile() const;
    void setSelectedConfigFile(const QString& value);
    bool loading() const;
    QString errorCode() const;

    Q_INVOKABLE void refreshConfigFiles();
    Q_INVOKABLE void loadSelectedConfigFile();

signals:
    void availableConfigFilesChanged();
    void selectedConfigFileChanged();
    void loadingChanged();
    void errorCodeChanged();

    void configFileLoaded(QString fileName);
    void configFileLoadFailed(QString fileName, QString errorCode);

signals:
    void requestRefreshConfigFiles();
    void requestLoadConfigFile(QString fileName);

private:
    void setAvailableConfigFiles(const QStringList& value);
    void setLoading(bool value);
    void setErrorCode(const QString& value);

    ShellFacade& shellFacade_;
    QThread workerThread_;
    ConfigFileWorker* worker_ = nullptr;

    QStringList availableConfigFiles_;
    QString selectedConfigFile_;
    bool loading_ = false;
    QString errorCode_;
};
