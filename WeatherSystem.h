#pragma once
#include <string>
#include <iostream>
#include "HistoryLogger.h"
#include "Forecast.h"
using namespace std;

class WeatherSystem {
private:
    HistoryLogger logger;

public:
    Forecast loadData(string cityName, string countryName);
    void logHistory(const string& userInput, const string& forecastResult);
};
