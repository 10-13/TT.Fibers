#pragma once

#include <cstdint>

namespace TT {
    namespace low {
        extern "C" void __TTLinux64_switch(uintptr_t* caller_stack_ptr, uintptr_t* callee_stack_ptr);
        extern "C" void __TTWindows64_switch(uintptr_t* caller_stack_ptr, uintptr_t* callee_stack_ptr);

        static uintptr_t __TTLinux64_prepare_for_exec(uintptr_t func, uintptr_t* data_end);
        static uintptr_t __TTWindows64_prepare_for_exec(uintptr_t func, uintptr_t* data_end);

        static void restore_core();
    }
}

