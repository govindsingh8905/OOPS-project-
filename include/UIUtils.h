#ifndef UIUTILS_H
#define UIUTILS_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

// Forward declarations (do NOT include Vehicle.h etc in this header)
class Vehicle;
class Customer;
class Rental;

class UIUtils {
public:
    static void clearScreen();
    static void printHeader(const std::string& title);
    static void printSubHeader(const std::string& title);
    static void printSeparator(char ch = '=', int width = 55);
    static void printDoubleSeparator(int width = 55);
    static void printSuccess(const std::string& msg);
    static void printError(const std::string& msg);
    static void printWarning(const std::string& msg);
    static void printInfo(const std::string& msg);
    static void pressEnterToContinue();
    
    static int getMenuChoice(int min, int max);
    static std::string getStringInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt, int min = 0, int max = 999999);
    static double getDoubleInput(const std::string& prompt, double min = 0.0);
    static bool getConfirmation(const std::string& prompt);
    
    static void printVehicleTableHeader();
    static void printVehicleTableRow(const Vehicle& v);
    static void printVehicleTableFooter();
    static void printVehicleTable(const std::vector<std::shared_ptr<Vehicle>>& vehicles);
    
    static void printCustomerTable(const std::vector<Customer>& customers);
    static void printRentalTable(const std::vector<Rental>& rentals);
    
    static void loadingAnimation(const std::string& msg, int durationMs = 800);
    static void printWelcomeScreen();
};

#endif
