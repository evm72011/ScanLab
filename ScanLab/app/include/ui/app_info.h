#pragma once

#include <QObject>
#include "configured/app_info.h"

class AppInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString version READ version CONSTANT)

public:
    explicit AppInfo(QObject* parent = nullptr) : QObject(parent) {}

    QString name() const {
        return QString::fromUtf8(project_name.data());
    }

    QString version() const {
        return QString::fromUtf8(project_version.data());
    }
};
