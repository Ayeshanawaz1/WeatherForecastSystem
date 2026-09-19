#pragma once
#include "City.h"
#include "Weather.h"
#include <vector>
#include <string>

using namespace std;

class Forecast {
private:
    City city; // Each forecast will be for a specific city
    vector<Weather> weather; // For storing objects of Weather class(Upto 7 days)

public:
    Forecast(string cityName = "", string countryName = "");

    void addWeather(const Weather& w);
    void saveToFile(const string& filename);
    bool loadFromFile(const string& filename);
    size_t getWeatherCount() const { return weather.size(); }
    Weather getWeatherAt(size_t index) const { return weather[index]; }

    //const vector<Weather>& getWeather() const {
    //    return weather;
    //}

    const Weather* findWeatherByDate(const string& date) const; // Used it server.cpp
    const City& getCity() const { return city; }

    //void displayForecastByWeek();
    //void displayForecastByDate(string day, string month, string year);
    //void displayHourlyForecast(string day, string month, string year);
};
