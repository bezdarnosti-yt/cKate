#include "Application.h"
#include <iostream>
#include <exception>

int main(int, char**){
    try {
        Application app;
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}