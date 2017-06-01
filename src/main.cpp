#include "Sketch.hpp"


int main(int argc, char **argv) {
    Sketch sketch(argc > 1 ? argv[1] : nullptr);

    sketch.setup();
    sketch.loop();
}