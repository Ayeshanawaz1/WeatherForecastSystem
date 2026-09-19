#pragma once
#include <iostream>
#include <string>
using namespace std;

class WeatherAPI {
public:
    static string fetchWeatherData(const string& cityName, const string& countryName);
};
