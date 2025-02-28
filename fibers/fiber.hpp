#pragma once

#include "fibers/scheduling/state.hpp"
#include "context.hpp"

using namespace TT::fibers::scheduling;

namespace TT {
    namespace fibers {
        struct fiber : private context, public state<fiber> {
            using fiberptr_t = fiber*;
        };
    }
}
