#pragma once

#include "configured/app_info.h"
#include <QObject>

class AppInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(bool isMockDevice READ isMockDevice CONSTANT)

public:
    explicit AppInfo(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    QString name() const
    {
        return QString::fromUtf8(project_name.data(), project_name.size());
    }

    QString version() const
    {
        return QString::fromUtf8(project_version.data(), project_version.size());
    }

    bool isMockDevice() const
    {
        return is_mock_device;
    }
};
