#pragma once

#include <optional>
#include <vector>

struct TemperatureSensor
{
    int board = 0;
    int sensor = 0;
    int valueCelsius = 0;
};

struct TemperatureSnapshot
{
    std::vector<TemperatureSensor> sensors;
    std::vector<int> maxPerBoardCelsius;

    bool empty() const;
    std::optional<int> overallMaxCelsius() const;
};