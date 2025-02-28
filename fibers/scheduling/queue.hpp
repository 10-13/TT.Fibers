#pragma once

#include "fiber.hpp"

namespace TT {
    namespace fibers {
        namespace scheduling {
            struct queue : fiber {
                using queueptr_t = queue*;
            };
        }
    }
}
