#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Weather {
private:
    string weatherCondition, year, month, day;
    float currentTemperature, windSpeed;
    int humidityPercentage;

    vector<string> hours;
    vector<string> hourConditions;
    vector<float> hourTemperatures;
    vector<int> hourHumidities;
    vector<float> hourWinds;

public:
    Weather(string weather = "", float temp = 0.0, int humidity = 0, float wind = 0.0,
        string _year = "", string _month = "", string _day = "");

    string getdateOfForecast() const;
    string getWeatherCondition() const { return weatherCondition; }
    float getCurrentTemperature() const { return currentTemperature; }
    int getHumidityPercentage() const { return humidityPercentage; }
    float getWindSpeed() const { return windSpeed; }

    const vector<string>& getHours() const { return hours; }
    const vector<string>& getHourConditions() const { return hourConditions; }
    const vector<float>& getHourTemperatures() const { return hourTemperatures; }
    const vector<int>& getHourHumidities() const { return hourHumidities; }
    const vector<float>& getHourWinds() const { return hourWinds; }
    void addHourlyData(string time, string condition, float temp, int humidity, float wind);

    //void displayWeather() const;
    //void displayHourlyForecast() const;
};