#pragma once
#include <string>

using namespace std;

class HistoryLogger {
private:
    const string filename = "weather_history.txt";

public:
    void logEntry(const string& userInput, const string& forecastResult);
};
