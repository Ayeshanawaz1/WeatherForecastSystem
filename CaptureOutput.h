#pragma once
#include <sstream>
#include <iostream>
#include "Forecast.h"

using namespace std;

inline string captureOutput(void (Forecast::* func)(), Forecast& forecast) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    (forecast.*func)();
    cout.rdbuf(old);
    return buffer.str();
}

inline string captureOutput(void (Forecast::* func)(string, string, string), Forecast& forecast, string y, string m, string d) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    (forecast.*func)(y, m, d);
    cout.rdbuf(old);
    return buffer.str();
}
