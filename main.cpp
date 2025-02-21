#include <iostream>
#include <cstdint>

void HelloWrold() {
    std::cout << "Hello, wrold!" << std::endl;
}

extern "C" void __TTLinux64_switch(uintptr_t* caller_stack_ptr, uintptr_t* callee_stack_ptr);

asm(R"(
__TTLinux64_switch:
    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %rbx
    pushq %rbp
    movq %rsp, (%rdi)

    movq (%rsi), %rsp
    popq %rbp
    popq %rbx
    popq %r12
    popq %r13
    popq %r14
    popq %r15
    ret
)");

extern "C" void __TTWindows64_switch(uintptr_t* caller_stack_ptr, uintptr_t* callee_stack_ptr);

asm(R"(
__TTWindows64_switch:
    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %rdi
    pushq %rsi
    pushq %rbx
    pushq %rbp
    movq %rsp, (%rcx)

    movq (%rdx), %rsp
    popq %rbp
    popq %rbx
    popq %rsi
    popq %rdi
    popq %r12
    popq %r13
    popq %r14
    popq %r15
    ret
)");

static uintptr_t core_ptr = 0, b_ptr = 0;
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

static void restore_core();

static uintptr_t __TTLinux64_prepare_for_exec(uintptr_t func, uintptr_t* data) {
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = (uintptr_t)func;
    data[8] = (uintptr_t)restore_core;
    return (uintptr_t)&data[1];
}


static uintptr_t __TTWindows64_prepare_for_exec(uintptr_t func, uintptr_t* data) {
    data = std::prev(data, 11);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    data[8] = 0;
    data[9] = (uintptr_t)func;
    data[10] = (uintptr_t)restore_core;
    return (uintptr_t)&data[1];
}

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

static void restore_core() {
    std::cout << "Restoring core" << std::endl;
    current_switcher::swticher(&b_ptr, &core_ptr);
}




void MyTest() {
    std::cout << "Something happend" << std::endl;
}

void MyExit() {
    std::cout << "Bye bye!";
    std::exit(10);
}

int main() {
    uintptr_t* a = new uintptr_t[100];
    std::cout << "Preparing b fiber:" << std::endl;
    b_ptr = current_switcher::preparer((uintptr_t)MyTest, a);
    std::cout << "Done!" << std::endl;
    std::cout << "Swtiching to b fiber:" << std::endl;
    current_switcher::swticher(&core_ptr, &b_ptr);
    std::cout << "Switched back!" << std::endl;
    MyExit();
}