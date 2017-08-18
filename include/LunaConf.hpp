#pragma once
#include "Configuration.hpp"
#include "Defines.hpp"

namespace luna_conf {
    static Configuration main(getLunaResource("luna.cfg"));
    static Configuration lang(getLunaResource("lang/" + main.get("lang") + ".lang"));
}