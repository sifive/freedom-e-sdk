/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <mee/shutdown.h>

#if defined(__MEE_DT_SHUTDOWN_HANDLE)
void mee_shutdown(int code)
{
    mee_shutdown_exit(__MEE_DT_SHUTDOWN_HANDLE, code);
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
