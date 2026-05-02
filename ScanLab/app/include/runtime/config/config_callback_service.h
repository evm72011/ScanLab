#pragma once

#include <QVariantMap>

#include <functional>

namespace scanlab::config {
struct ConfigSnapshot;
}

class ConfigCallbackService {
public:
    using SnapshotHandler = std::function<void(QVariantMap)>;

    ConfigCallbackService();
    ~ConfigCallbackService();

    void startWatching(SnapshotHandler handler);
    void stopWatching();

private:
    static QVariantMap toVariantMap(
        const scanlab::config::ConfigSnapshot& snapshot);
};
