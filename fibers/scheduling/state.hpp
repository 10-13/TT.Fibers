#pragma once

#include <cstdint>

#include "fibers/fiber.hpp"

namespace TT {
    namespace fibers {
        namespace scheduling {
            template<typename T>
            struct state {
                using cr_ptr_t = T*;

                cr_ptr_t next, prev;

                constexpr state() noexcept : next(this), prev(this) {}

                [[always_inline]] constexpr bool is_empty() noexcept {
                    return next == prev && prev == this;
                }

                [[always_inline]] constexpr void unlink() noexcept {
                    next->prev = prev;
                    prev->next = next;
                    next = prev = this;
                }

                [[always_inline]] constexpr void merge(cr_ptr_t obj) noexcept {
                    cr_ptr_t o_last = prev;
                    prev = obj->prev;
                    o_last->next = obj;
                    obj->prev = o_last;
                    prev->next = this;
                }

                [[always_inline]] constexpr cr_ptr_t split() noexcept {
                    cr_ptr_t res = next;
                    unlink();
                    return res;
                }

                constexpr ~state() noexcept {
                    unlink();
                }
            };
        }
    }
}