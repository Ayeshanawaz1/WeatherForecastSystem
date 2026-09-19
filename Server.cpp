// server.cpp
// Must define these BEFORE including windows.h to avoid std::byte conflicts
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "WeatherSystem.h"
#include "httplib.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include "json.hpp"

using namespace std;
using namespace httplib;
using json = nlohmann::json;

std::string getCurrentDate() {
    time_t now = time(0);
    tm localTime;
#ifdef _MSC_VER
    localtime_s(&localTime, &now);
#else
    localTime = *localtime(&now);
#endif
    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &localTime);
    return std::string(dateStr);
}

std::string weatherToJson(const Weather& w, bool includeHourly = false) {
    json j;
    j["date"] = w.getdateOfForecast();
    j["condition"] = w.getWeatherCondition();
    j["temperature"] = w.getCurrentTemperature();
    j["humidity"] = w.getHumidityPercentage();
    j["windSpeed"] = w.getWindSpeed();

    if (includeHourly) {
        json hourlyArray = json::array();
        // Assuming you have getters for hourly data in Weather class
        const auto& hours = w.getHours();
        const auto& conditions = w.getHourConditions();
        const auto& temps = w.getHourTemperatures();
        const auto& humidities = w.getHourHumidities();
        const auto& winds = w.getHourWinds();

        for (size_t i = 0; i < hours.size(); i++) {
            json hourJson;
            hourJson["time"] = hours[i];
            hourJson["condition"] = conditions[i];
            hourJson["temperature"] = temps[i];
            hourJson["humidity"] = humidities[i];
            hourJson["windSpeed"] = winds[i];
            hourlyArray.push_back(hourJson);
        }
        j["hourly"] = hourlyArray;
    }

    return j.dump();
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }

    Server svr;
    WeatherSystem weatherSystem;

    // Set document root for static files
    svr.set_mount_point("/", "./static");

    // Add CORS headers to all responses
    svr.set_post_routing_handler([](const Request& req, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });

    // API endpoint for weather data
    svr.Get("/api/weather", [&](const Request& req, Response& res) {
        std::string city = req.get_param_value("city");
        std::string country = req.get_param_value("country");
        std::string date = req.get_param_value("date");
        std::string type = req.get_param_value("type");

        if (city.empty() || country.empty()) {
            res.set_content("{\"error\":\"City and country are required\"}", "application/json");
            return;
        }

        Forecast forecast = weatherSystem.loadData(city, country);

        if (type == "weekly") {
            json response;
            response["city"] = forecast.getCity().getcityName();
            response["country"] = forecast.getCity().getcountryName();

            json forecastArray = json::array();
            for (size_t i = 0; i < forecast.getWeatherCount(); i++) {
                Weather w = forecast.getWeatherAt(i);
                json dayJson;
                dayJson["date"] = w.getdateOfForecast();
                dayJson["condition"] = w.getWeatherCondition();
                dayJson["temperature"] = w.getCurrentTemperature();
                dayJson["humidity"] = w.getHumidityPercentage();
                dayJson["windSpeed"] = w.getWindSpeed();
                forecastArray.push_back(dayJson);
            }
            response["forecast"] = forecastArray;

            std::cout << "Sending response: " << response.dump(2) << std::endl;

            res.set_content(response.dump(), "application/json");
        }
        else if (type == "daily" || type == "hourly") {
            if (date.empty()) date = getCurrentDate();

            const Weather* w = forecast.findWeatherByDate(date);
            if (w) {
                json response;
                response["city"] = forecast.getCity().getcityName();
                response["country"] = forecast.getCity().getcountryName();
                response["date"] = date;

                if (type == "daily") {
                    response["condition"] = w->getWeatherCondition();
                    response["temperature"] = w->getCurrentTemperature();
                    response["humidity"] = w->getHumidityPercentage();
                    response["windSpeed"] = w->getWindSpeed();
                }
                else { // hourly
                    json hourlyArray = json::array();
                    // Assuming you have getters for hourly data in Weather class
                    const auto& hours = w->getHours();
                    const auto& conditions = w->getHourConditions();
                    const auto& temps = w->getHourTemperatures();
                    const auto& humidities = w->getHourHumidities();
                    const auto& winds = w->getHourWinds();

                    for (size_t i = 0; i < hours.size(); i++) {
                        json hourJson;
                        hourJson["time"] = hours[i];
                        hourJson["condition"] = conditions[i];
                        hourJson["temperature"] = temps[i];
                        hourJson["humidity"] = humidities[i];
                        hourJson["windSpeed"] = winds[i];
                        hourlyArray.push_back(hourJson);
                    }
                    response["hourly"] = hourlyArray;
                }

                res.set_content(response.dump(), "application/json");
            }
            else {
                res.set_content("{\"error\":\"No data for specified date\"}", "application/json");
            }
        }
        else {
            res.set_content("{\"error\":\"Invalid forecast type\"}", "application/json");
        }
        });

    // Add this near your other endpoints in Server.cpp
    svr.Get("/api/history", [&](const Request& req, Response& res) {
        ifstream historyFile("weather_history.txt");
        if (historyFile.is_open()) {
            string content((istreambuf_iterator<char>(historyFile)),
                (istreambuf_iterator<char>()));
            res.set_content(content, "text/plain");
        }
        else {
            res.set_content("No history available", "text/plain");
        }
        });

    svr.Post("/api/log", [&](const Request& req, Response& res) {
        auto json = nlohmann::json::parse(req.body);
        string city = json["city"];
        string country = json["country"];
        string type = json["type"];
        string date = json.value("date", "");

        string userInput = city + ", " + country + " (" + type;
        if (!date.empty()) {
            userInput += " for " + date;
        }
        userInput += ")";

        weatherSystem.logHistory(userInput, "Search recorded");
        res.set_content("{\"status\":\"success\"}", "application/json");
        });

    std::cout << "Server running on http://localhost:8080\n";
    svr.listen("localhost", 8080);

    // Cleanup Winsock
    WSACleanup();
    return 0;
}