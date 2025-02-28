#pragma once

#include <cstdint>

namespace TT {
    namespace fibers {
        struct context {
        public:
            uintptr_t rsp;
        };
    }
}

