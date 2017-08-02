#include "Sketch.hpp"

int main(int argc, char **argv) {
    if (Sketch::instance().preload(argc > 1 ? argv[1] : nullptr))
        return EXIT_FAILURE;
    
    if (Sketch::instance().setup())
        return EXIT_FAILURE;
    
    Sketch::instance().loop();
    Sketch::instance().cleanup();

    return EXIT_SUCCESS;
}