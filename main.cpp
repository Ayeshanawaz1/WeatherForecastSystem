//#include <iostream>
//#include <string>
//#include "City.h"
//#include "Weather.h"
//#include "Forecast.h"
//#include "HistoryLogger.h"  
//#include "WeatherAPI.h"     
//#include "WeatherSystem.h" 
//#include "CaptureOutput.h"
//
//using namespace std;
//
//void displayWelcome() {
//    cout << "==============================================" << endl;
//    cout << "        Welcome to Weather Forecast       " << endl;
//    cout << "  Plan your week with confidence and clarity!  " << endl;
//    cout << "==============================================" << endl;
//}
//
//bool getUserLocation(string& countryName, string& cityName) {
//    cout << "\nEnter Country Name (or 'q' to quit): ";
//    getline(cin, countryName);
//    if (countryName == "q") return false;
//
//    cout << "Enter City Name (or 'q' to quit): ";
//    getline(cin, cityName);
//    if (cityName == "q") return false;
//
//    return true;
//}
//
//int getUserChoice() {
//    cout << "\nDo you want the forecast for:\n";
//    cout << "0: Back to location input\n";
//    cout << "1. Whole Week\n";
//    cout << "2. Specific Day\n";
//    cout << "3. Hourly Forecast\n";
//    cout << "Enter your choice (0-3): ";
//
//    int choice;
//    cin >> choice;
//    cin.ignore();
//    return choice;
//}
//
//void getDateInput(string& year, string& month, string& day) {
//    cout << "Enter Year (YYYY): ";
//    getline(cin, year);
//    cout << "Enter Month (MM): ";
//    getline(cin, month);
//    cout << "Enter Day (DD): ";
//    getline(cin, day);
//}
//
//bool askToContinue() {
//    cout << "\nWould you like to:\n";
//    cout << "1. Get another forecast\n";
//    cout << "2. Change location\n";
//    cout << "3. Exit program\n";
//    cout << "Enter choice (1-3): ";
//
//    int choice;
//    cin >> choice;
//    cin.ignore();
//
//    if (choice == 1) return true;  // Continue with same location
//    if (choice == 2) return false; // Change location
//    cout << "Exiting the program. Goodbye!" << endl;
//    exit(0);
//}
//
//int main() {
//    displayWelcome();
//
//    while (true) {
//        string countryName, cityName;
//        if (!getUserLocation(countryName, cityName)) {
//            cout << "Exiting the program. Goodbye!" << endl;
//            break;
//        }
//
//        string userInput = "City: " + cityName + ", Country: " + countryName;
//        WeatherSystem system1;
//        Forecast f1 = system1.loadData(cityName, countryName);
//
//        bool sameLocation = true;
//        while (sameLocation) {
//            int choice = getUserChoice();
//            string forecastResult;
//
//            if (choice == 0) {
//                break; // Goes back to location input
//            }
//            else if (choice == 1) {
//                forecastResult = captureOutput(&Forecast::displayForecastByWeek, f1);
//                f1.displayForecastByWeek();
//            }
//            else if (choice == 2) {
//                string year, month, day;
//                getDateInput(year, month, day);
//                forecastResult = captureOutput(&Forecast::displayForecastByDate, f1, year, month, day);
//                f1.displayForecastByDate(year, month, day);
//            }
//            else if (choice == 3) {
//                string year, month, day;
//                getDateInput(year, month, day);
//                forecastResult = captureOutput(&Forecast::displayHourlyForecast, f1, year, month, day);
//                f1.displayHourlyForecast(year, month, day);
//            }
//            else {
//                cout << "Invalid choice. Please try again." << endl;
//                continue;
//            }
//
//            system1.logHistory(userInput, forecastResult);
//            cout << "\nYour forecast has been saved to weather_history.txt\n";
//
//            sameLocation = askToContinue();
//        }
//    }
//
//    return 0;
//}