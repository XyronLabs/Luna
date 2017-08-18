#include <cstring>

#include "Sketch.hpp"
#include "Logger.hpp"
#include "Defines.hpp"
#include "Configuration.hpp"
#include "LunaConf.hpp"

int main(int argc, char **argv) {
    
    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        std::cout << "Luna version: " << LUNA_VERSION << " | build date: " << __DATE__ << " " << __TIME__ << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << luna_conf::main << std::endl;
    std::cout << luna_conf::lang << std::endl;

    Logger::instance().setLevel(Logger::Level::INFO);
    Logger::instance().log(Logger::Level::INFO, { luna_conf::lang.get("luna_starting") });

    if (!Sketch::instance().preload(argc > 1 ? argv[1] : nullptr) && !Sketch::instance().setup())
        Sketch::instance().loop();
    
    Sketch::instance().cleanup();


    Logger::instance().log(Logger::Level::INFO, { luna_conf::lang.get("luna_exiting") });
    
    return EXIT_SUCCESS;
}