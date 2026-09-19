#include "Forecast.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

Forecast::Forecast(string cityName, string countryName)
    : city(cityName, countryName) {
}

void Forecast::addWeather(const Weather& w) {
    weather.push_back(w);
}

const Weather* Forecast::findWeatherByDate(const string& date) const {
    for (const auto& w : weather) {
        if (w.getdateOfForecast() == date) {
            return &w;
        }
    }
    return nullptr;
}

//void Forecast::displayForecastByWeek() {
//    cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
//    cout << "=============================\n";
//    for (size_t i = 0; i < weather.size(); i++) {
//        cout << "Day " << (i + 1) << ":\n";
//        weather[i].displayWeather();
//    }
//}
//
//void Forecast::displayForecastByDate(string year, string month, string day) {
//
//    if (day.length() == 1) day = "0" + day;
//    if (month.length() == 1) month = "0" + month;
//    string inputDate = year + "-" + month + "-" + day;
//    bool found = false;
//    
//
//    for (Weather& w : weather) {
//        if (w.getdateOfForecast() == inputDate) {
//            cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
//            w.displayWeather();
//            found = true;
//            break;
//        }
//    }
//
//    if (!found) {
//        cout << "No forecast available for " << day << "/" << month << "/" << year
//            << " in " << city.getcityName() << ", " << city.getcountryName() << "." << endl;
//        for (Weather& w : weather) {
//            cout << "DEBUG: Available date: " << w.getdateOfForecast() << endl;
//        }
//    }
//}
//
//void Forecast::displayHourlyForecast(string year, string month, string day) {
//    if (day.length() == 1) day = "0" + day;
//    if (month.length() == 1) month = "0" + month;
//    string inputDate = year + "-" + month + "-" + day;
//    bool found = false;
//
//    for (Weather& w : weather) {
//        if (w.getdateOfForecast() == inputDate) {
//            cout << "\nHourly Forecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
//            w.displayHourlyForecast();
//            found = true;
//            break;
//        }
//    }
//
//    if (!found) {
//        cout << "No hourly forecast available for " << day << "/" << month << "/" << year
//            << " in " << city.getcityName() << ", " << city.getcountryName() << "." << endl;
//
//        for (Weather& w : weather) {
//            cout << "DEBUG: Available date: " << w.getdateOfForecast() << endl;
//        }
//    }
//}

void Forecast::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    // Save city info
    outFile << city.getcityName() << "\n";
    outFile << city.getcountryName() << "\n";

    // Save weather data
    outFile << weather.size() << "\n";
    for (const auto& w : weather) {
        outFile << w.getdateOfForecast() << "\n";
        outFile << w.getCurrentTemperature() << "\n";
        outFile << w.getHumidityPercentage() << "\n";
        outFile << w.getWindSpeed() << "\n";
        outFile << w.getWeatherCondition() << "\n";

        // Save hourly data
        const auto& hours = w.getHours();
        outFile << hours.size() << "\n";
        for (size_t i = 0; i < hours.size(); i++) {
            outFile << hours[i] << "\n";
            outFile << w.getHourConditions()[i] << "\n";
            outFile << w.getHourTemperatures()[i] << "\n";
            outFile << w.getHourHumidities()[i] << "\n";
            outFile << w.getHourWinds()[i] << "\n";
        }
    }
    outFile.close();
}

bool Forecast::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return false;
    }

    weather.clear();

    // Load city info
    string cityName, countryName;
    getline(inFile, cityName);
    getline(inFile, countryName);
    city = City(cityName, countryName);

    // Load weather data
    size_t weatherCount;
    inFile >> weatherCount;
    inFile.ignore(); // Skip newline

    for (size_t i = 0; i < weatherCount; i++) {
        string date, condition;
        float temp, wind;
        int humidity;

        getline(inFile, date);
        inFile >> temp;
        inFile >> humidity;
        inFile >> wind;
        inFile.ignore(); // Skip newline
        getline(inFile, condition);

        // Parse date (assuming format YYYY-MM-DD)
        string year = date.substr(0, 4);
        string month = date.substr(5, 2);
        string day = date.substr(8, 2);

        Weather w(condition, temp, humidity, wind, year, month, day);

        // Load hourly data
        size_t hourCount;
        inFile >> hourCount;
        inFile.ignore(); // Skip newline

        for (size_t j = 0; j < hourCount; j++) {
            string time, h_condition;
            float h_temp, h_wind;
            int h_humidity;

            getline(inFile, time);
            getline(inFile, h_condition);
            inFile >> h_temp;
            inFile >> h_humidity;
            inFile >> h_wind;
            inFile.ignore(); // Skip newline

            w.addHourlyData(time, h_condition, h_temp, h_humidity, h_wind);
        }

        weather.push_back(w);
    }

    inFile.close();
    return true;
}