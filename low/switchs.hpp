#pragma once

#include "fwd.hpp"

namespace TT {
    namespace low {
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

    }
}