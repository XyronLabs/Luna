#include <cstring>

#include "Sketch.hpp"
#include "Logger.hpp"
#include "Defines.hpp"

int main(int argc, char **argv) {
    
    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        std::cout << "Luna version: " << LUNA_VERSION << " | build date: " << __DATE__ << " " << __TIME__ << std::endl;
        return EXIT_SUCCESS;
    }

    Logger::instance().setLevel(Logger::Level::INFO);
    Logger::instance().log(Logger::Level::INFO, {"Starting Luna..."});

    if (Sketch::instance().preload(argc > 1 ? argv[1] : nullptr))
        return EXIT_FAILURE;
    
    if (Sketch::instance().setup())
        return EXIT_FAILURE;
    
    Sketch::instance().loop();
    Sketch::instance().cleanup();


    Logger::instance().log(Logger::Level::INFO, {"Exiting Luna..."});
    
    return EXIT_SUCCESS;
}