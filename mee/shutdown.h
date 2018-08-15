/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef MEE__SHUTDOWN_H
#define MEE__SHUTDOWN_H

struct __mee_shutdown;

struct __mee_shutdown_vtable {
    void (*exit)(const struct __mee_shutdown *sd, int code) __attribute__((noreturn));
};

struct __mee_shutdown {
    const struct __mee_shutdown_vtable *vtable;
};

inline void __mee_shutdown_exit(const struct __mee_shutdown *sd, int code) __attribute__((noreturn));
inline void __mee_shutdown_exit(const struct __mee_shutdown *sd, int code) { sd->vtable->exit(sd, code); }

/* The public MEE shutdown interface, which allows us to turn off the machine
 * when posible. */
void mee_shutdown(int code) __attribute__((noreturn));

#endif
