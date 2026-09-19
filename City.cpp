#include "City.h"

City::City(string city, string country)
    : cityName(city), countryName(country){
}

string City::getcityName() const { return cityName; }
string City::getcountryName() const { return countryName; }

//void City::displayCity() {
//    cout << "City: " << cityName << ", Country: " << countryName << endl;
//}
