#include "Weather.h"

Weather::Weather(string weather, float temp, int humidity, float wind,
    string _year, string _month, string _day)
    : weatherCondition(weather), currentTemperature(temp), humidityPercentage(humidity),
    windSpeed(wind), year(_year), month(_month), day(_day) {}

string Weather::getdateOfForecast() const{
    return year + "-" + month + "-" + day;
}

//void Weather::displayWeather() const{
//    cout << "Date: " << day << "/" << month << "/" << year << endl;
//    cout << "Condition: " << weatherCondition << endl;
//    cout << "Temperature: " << currentTemperature << "°C" << endl;
//    cout << "Humidity: " << humidityPercentage << "%" << endl;
//    cout << "Wind Speed: " << windSpeed << " km/h" << endl;
//    cout << "-----------------------------" << endl;
//}
//
void Weather::addHourlyData(string time, string condition, float temp, int humidity, float wind) {
    hours.push_back(time);
    hourConditions.push_back(condition);
    hourTemperatures.push_back(temp);
    hourHumidities.push_back(humidity);
    hourWinds.push_back(wind);
}

//void Weather::displayHourlyForecast() const{
//    cout << "\nHOURLY FORECAST:\n------------------------\n";
//    for (size_t i = 0; i < hours.size(); i++) {
//        cout << "Time: " << hours[i] << endl;
//        cout << "Condition: " << hourConditions[i] << endl;
//        cout << "Temperature: " << hourTemperatures[i] << "°C" << endl;
//        cout << "Humidity: " << hourHumidities[i] << "%" << endl;
//        cout << "Wind Speed: " << hourWinds[i] << " km/h" << endl;
//        cout << "-----------------------------\n";
//    }
//} 