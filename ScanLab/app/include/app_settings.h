#pragma once

#include <QObject>
#include <QSettings>
#include <qqmlintegration.h>

class AppSettings : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit AppSettings(QObject* parent = nullptr)
        : QObject(parent)
        , settings_("config.ini", QSettings::IniFormat)
    {
    }

    Q_INVOKABLE QVariant value(const QString& key, const QVariant& defaultValue = {}) const
    {
        return settings_.value(key, defaultValue);
    }

    Q_INVOKABLE void setValue(const QString& key, const QVariant& value)
    {
        settings_.setValue(key, value);
    }

private:
    mutable QSettings settings_;
};
