#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include "ui/shell/shell_facade.h"

class DeviceContext;
class ConfigFileWorker;

class ConfigFileFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(QString loadPath READ loadPath WRITE setLoadPath NOTIFY loadPathChanged)
    Q_PROPERTY(QString savePath READ savePath WRITE setSavePath NOTIFY savePathChanged)

public:
    explicit ConfigFileFacade(DeviceContext& context,
        ShellFacade& shellFacade,
        QObject* parent = nullptr);
    ~ConfigFileFacade() override;

    QString loadPath() const;
    QString savePath() const;
    bool busy() const;

    void setLoadPath(const QString& value);
    void setSavePath(const QString& value);

    Q_INVOKABLE void loadConfigFile();
    Q_INVOKABLE void saveConfigFile();

signals:
    void busyChanged();
    void loadPathChanged();
    void savePathChanged();

signals:
    void requestLoad();
    void requestSave();

private:
    void setBusy(bool value);

    ShellFacade& shellFacade_;
    QThread workerThread_;
    ConfigFileWorker* worker_ = nullptr;

    QString loadPath_;
    QString savePath_;
    bool busy_ = false;
};
