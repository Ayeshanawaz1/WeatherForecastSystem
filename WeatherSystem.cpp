#include "WeatherSystem.h"
#include "WeatherAPI.h"
#include "Forecast.h"
#include "json.hpp"
#include <iostream>
#include <ctime>

using namespace std;
using json = nlohmann::json;

Forecast WeatherSystem::loadData(string cityName, string countryName) {
    Forecast forecast(cityName, countryName);

    string response = WeatherAPI::fetchWeatherData(cityName, countryName);

    if (response.empty()) {
        cout << "Failed to fetch weather data. Check your internet connection." << endl;
        return forecast;
    }

    try {
        json data = json::parse(response);

        // Check if the API returned an error
        if (data.contains("error")) {
            string errorMsg = data["error"]["message"];
            cout << "API Error: " << errorMsg << endl;
            return forecast;
        }

        // Use the city/country from the API response for display
        // (don't reject valid responses just because names don't match exactly)
        string actualCity = data["location"]["name"];
        string actualCountry = data["location"]["country"];

        // Update forecast with the actual names from the API
        forecast = Forecast(actualCity, actualCountry);

        auto days = data["forecast"]["forecastday"];
        for (auto& day : days) {
            string date = day["date"];
            string year = date.substr(0, 4);
            string month = date.substr(5, 2);
            string dayPart = date.substr(8, 2);

            string condition = day["day"]["condition"]["text"];
            float temp = day["day"]["avgtemp_c"];
            int humidity = day["day"]["avghumidity"];
            float wind = day["day"]["maxwind_kph"];

            Weather w(condition, temp, humidity, wind, year, month, dayPart);

            for (auto& hour : day["hour"]) {
                string time = hour["time"];
                string h_condition = hour["condition"]["text"];
                float h_temp = hour["temp_c"];
                int h_humidity = hour["humidity"];
                float h_wind = hour["wind_kph"];

                w.addHourlyData(time, h_condition, h_temp, h_humidity, h_wind);
            }

            forecast.addWeather(w);
        }

    }
    catch (const exception& e) {
        cout << "Error parsing JSON data: " << e.what() << endl;
    }
    catch (...) {
        cout << "Error parsing JSON data!" << endl;
    }

    return forecast;
}

void WeatherSystem::logHistory(const string& userInput, const string& forecastResult) {
    logger.logEntry(userInput, forecastResult);
}
