#pragma once
#include "luna/Configuration.hpp"
#include "luna/Defines.hpp"

namespace luna_conf {
    static Configuration main(getLunaResource("luna.cfg"));
    static Configuration lang(getLunaResource("lang/" + main.get("lang") + ".lang"));
}