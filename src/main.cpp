#include "RentalSystem.h"
#include <iostream>

int main() {
    try {
        RentalSystem system;
        system.run();
    } catch (const std::exception& e) {
        std::cerr << "\n[FATAL ERROR] An unexpected exception occurred: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n[FATAL ERROR] An unknown error occurred." << std::endl;
        return 1;
    }
    return 0;
}

