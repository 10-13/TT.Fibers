#pragma once

#include "fwd.hpp"

namespace TT {
    namespace low {
        static uintptr_t __TTLinux64_prepare_for_exec(uintptr_t func, uintptr_t* data_end) {
            data_end -= 9;
            data_end[0] = 0;
            data_end[1] = 0;
            data_end[2] = 0;
            data_end[4] = 0;
            data_end[5] = 0;
            data_end[6] = 0;
            data_end[7] = (uintptr_t)func;
            data_end[8] = (uintptr_t)restore_core;
            return (uintptr_t)&data_end[1];
        }

        static uintptr_t __TTWindows64_prepare_for_exec(uintptr_t func, uintptr_t* data_end) {
            data_end -= 11;
            data_end[0] = 0;
            data_end[1] = 0;
            data_end[2] = 0;
            data_end[4] = 0;
            data_end[5] = 0;
            data_end[6] = 0;
            data_end[7] = 0;
            data_end[8] = 0;
            data_end[9] = (uintptr_t)func;
            data_end[10] = (uintptr_t)restore_core;
            return (uintptr_t)&data_end[1];
        }
    }
}