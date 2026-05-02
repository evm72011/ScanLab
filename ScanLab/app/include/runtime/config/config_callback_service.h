#pragma once

#include <QVariantMap>
#include <functional>

class DeviceContext;

namespace scanlab::config {
struct ConfigSnapshot;
}

class ConfigCallbackService {
public:
    using SnapshotHandler = std::function<void(QVariantMap)>;

    explicit ConfigCallbackService(DeviceContext& context);
    ~ConfigCallbackService();

    void startWatching(SnapshotHandler handler);
    void stopWatching();

private:
    DeviceContext& context_;

    static QVariantMap toVariantMap(
        const scanlab::config::ConfigSnapshot& snapshot);
};
