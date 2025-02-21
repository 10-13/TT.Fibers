#pragma once

namespace TT {
    namespace low {
        struct arch {
            enum class processor {
                x86,
                x64,
                Undefined,
            };
            enum class os {
                Linux,
                Windows,
                Undefined,
            };
        
            constexpr const static bool __x86 =
            #ifdef __i386__
            true;
            #else
            false;
            #endif
        
            constexpr const static bool __x64 =
            #ifdef __x86_64__
            true;
            #else
            false;
            #endif
        
            constexpr const static bool __Win =
            #if defined(_WIN32) || defined(_WIN64) || defined(_CYGWIN)
            true;
            #else
            false;
            #endif
        
            constexpr const static bool __Linux =
            #if defined(__linux__) || defined(__gnu_linux__) 
            true;
            #else
            false;
            #endif
        
            constexpr const static os CurrentOS = __Win ? os::Windows : (__Linux ? os::Linux : os::Undefined);
            constexpr const static processor CurrentArch = __x86_64 ? processor::x64 : (__x86 ? processor::x86 : processor::Undefined);
        };
    }
}