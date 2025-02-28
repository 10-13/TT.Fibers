#pragma once

#include "queue.hpp"


namespace TT {
    namespace fibers {
        namespace scheduling {
            struct futex : protected queue {
            private:
                [[always_inline]] constexpr queueptr_t& waiting() noexcept {
                    return (queueptr_t&)this->next;
                }

                constexpr void place_to_queue(fiberptr_t f) noexcept {
                    if (waiting() == nullptr) {
                        waiting() = (queueptr_t)f;
                    } else {
                        waiting()->merge(f);
                    }
                }

                constexpr fiberptr_t pop_from_queue() noexcept {
                    fiberptr_t res = (fiberptr_t)waiting();
                    if (waiting()->next == waiting()) {
                        waiting() = nullptr;
                    } else {
                        waiting() = (queueptr_t)res->split();
                    }
                    return res;
                }

                [[always_inline]] constexpr fiberptr_t& owner() noexcept {
                    return this->prev;
                }

            public:
                [[always_inline]] const constexpr fiberptr_t& owner() const noexcept {
                    return this->prev;
                }

                constexpr bool is_owned() noexcept {
                    return owner() != nullptr;
                }

                constexpr void wait(fiberptr_t initiator) noexcept {
                    if (is_owned()) {
                        initiator->unlink();
                        place_to_queue(initiator);
                    } else {
                        owner() = initiator;
                    }
                }

                constexpr fiberptr_t notify_one() noexcept {
                    if (!is_owned() || waiting() == nullptr) {
                        return nullptr;
                    } else {
                        return pop_from_queue();
                    }
                }

                constexpr fiberptr_t notify_all() noexcept {
                    if (!is_owned()) {
                        return nullptr;
                    } else {
                        auto res = waiting();
                        waiting() = nullptr;
                        return res;
                    }
                }
            };
        }
    }
}
