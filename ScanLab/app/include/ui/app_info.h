#include <QObject>
#include "version.hpp"

class AppInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version CONSTANT)

public:
    explicit AppInfo(QObject* parent = nullptr) : QObject(parent) {}

    QString version() const {
        return QString::fromUtf8(project_version.data());
    }
};
