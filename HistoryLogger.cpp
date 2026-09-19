// HistoryLogger.cpp
#include "HistoryLogger.h"
#include <fstream>
#include <iostream>
#include <ctime>

void HistoryLogger::logEntry(const string& userInput, const string& forecastResult) {
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        time_t now = time(0);
        tm localTime;
#ifdef _MSC_VER
        localtime_s(&localTime, &now);
#else
        localTime = *localtime(&now);
#endif
        char timeStr[80];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);

        outFile << "[" << timeStr << "]\n";
        outFile << "User Input: " << userInput << "\n";
        outFile << "Forecast Result:\n" << forecastResult << "\n";
        outFile << "----------------------------------------\n";
        outFile.close();
    }
    else {
        cerr << "Error: Unable to open history file!" << endl;
    }
}
