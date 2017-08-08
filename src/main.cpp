#include "Sketch.hpp"
#include "Logger.hpp"

int main(int argc, char **argv) {
    Logger::instance().setLevel(Logger::Level::INFO);
    Logger::instance().logInfo("Starting Luna...");

    if (Sketch::instance().preload(argc > 1 ? argv[1] : nullptr))
        return EXIT_FAILURE;
    
    if (Sketch::instance().setup())
        return EXIT_FAILURE;
    
    Sketch::instance().loop();
    Sketch::instance().cleanup();


    Logger::instance().logInfo("Exiting Luna...");
    return EXIT_SUCCESS;
}