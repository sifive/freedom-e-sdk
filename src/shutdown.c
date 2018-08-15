/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/machine.h>
#include <mee/shutdown.h>

extern inline void __mee_shutdown_exit(const struct __mee_shutdown *sd, int code);

#if defined(__MEE_DT_SHUTDOWN_HANDLE)
void mee_shutdown(int code)
{
    __mee_shutdown_exit(__MEE_DT_SHUTDOWN_HANDLE, code);
}
#else
# warning "There is no defined shutdown mechanism, mee_shutdown() will spin."
void mee_shutdown(int code)
{
    while (1) {
      __asm__ volatile ("nop");
    }
}
#endif
