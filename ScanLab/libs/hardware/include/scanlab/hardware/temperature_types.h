#pragma once

#include <optional>
#include <vector>

namespace scanlab::hardware {

struct TemperatureSensorReading
{
    int board = 0;
    int sensor = 0;
    int valueCelsius = 0;
};

struct TemperatureSnapshot
{
    std::vector<TemperatureSensorReading> sensors;
    std::vector<int> boardMaxCelsius;

    [[nodiscard]] bool empty() const;
    [[nodiscard]] std::optional<int> overallMaxCelsius() const;
};
}// namespace scanlab::hardware