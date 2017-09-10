#include <cstring>

#include "Sketch.hpp"
#include "Logger.hpp"
#include "Defines.hpp"
#include "Configuration.hpp"
#include "LunaConf.hpp"

int main(int argc, char **argv) {

    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            std::cout << "Luna version: " << LUNA_VERSION << " | build date: " << __DATE__ << " " << __TIME__ << std::endl;
            return EXIT_SUCCESS;

        } else if (strcmp(argv[i], "-r") == 0 && argv[i + 1]) {
            // Set custom resources folder
            std::cout << argv[i+1] << std::endl;
        }
    }

    Logger::instance().setLevel(Logger::Level::INFO);
    Logger::instance().log(Logger::Level::INFO, { luna_conf::lang.get("luna_starting") });

    if (!Sketch::instance().preload(argc > 1 ? argv[1] : nullptr) && !Sketch::instance().setup())
        Sketch::instance().loop();
    
    Sketch::instance().cleanup();


    Logger::instance().log(Logger::Level::INFO, { luna_conf::lang.get("luna_exiting") });
    
    return EXIT_SUCCESS;
}