#pragma once
#include <string>
#include <iostream>

using namespace std;

class City {
private:
    string cityName, countryName;

public:
    City(string city = "", string country = "");

    string getcityName() const;
    string getcountryName() const;
    //void displayCity();
};
