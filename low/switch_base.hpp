#pragma once

#include "arch.hpp"
#include "fwd.hpp"

namespace TT {
    namespace low {
        using switch_func = void(*)(uintptr_t*, uintptr_t*);
        using prep_func = uintptr_t(*)(uintptr_t, uintptr_t*);

        template<arch::os OS, arch::processor Proc>
        struct switcher_base;

        template<>
        struct switcher_base<arch::os::Linux, arch::processor::x64> {
            constexpr static const switch_func swticher = __TTLinux64_switch;
            constexpr static const prep_func preparer = __TTLinux64_prepare_for_exec;
        };

        template<>
        struct switcher_base<arch::os::Windows, arch::processor::x64> {
            constexpr static const switch_func swticher = __TTWindows64_switch;
            constexpr static const prep_func preparer = __TTWindows64_prepare_for_exec;
        };

        using current_switcher = switcher_base<arch::CurrentOS, arch::CurrentArch>;
    }
}