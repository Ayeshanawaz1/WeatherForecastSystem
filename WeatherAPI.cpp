#include "WeatherAPI.h"
#include "httplib.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

string urlEncode(const string& value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (char c : value) {
        // Keep alphanumeric and other allowed characters as-is
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << '%' << setw(2) << int((unsigned char)c);
    }

    return escaped.str();
}

string WeatherAPI::fetchWeatherData(const string& cityName, const string& countryName) {
    string apiKey = "2b959b3ca5cd4079b0c135226261909"; // your API key

    string encodedCity = urlEncode(cityName);
    string encodedCountry = urlEncode(countryName);

    string path = "/v1/forecast.json?key=" + apiKey + "&q=" + encodedCity + "," + encodedCountry + "&days=7";

    // Use httplib::Client to make the HTTP request (no curl dependency needed)
    httplib::Client cli("http://api.weatherapi.com");
    cli.set_connection_timeout(10, 0);  // 10 seconds
    cli.set_read_timeout(10, 0);        // 10 seconds

    auto res = cli.Get(path);

    if (res) {
        if (res->status == 200) {
            return res->body;
        }
        else {
            cout << "API Error: HTTP " << res->status << " - " << res->body << endl;
            return "";
        }
    }
    else {
        auto err = res.error();
        cout << "Connection Error: " << httplib::to_string(err) << endl;
        return "";
    }
}
