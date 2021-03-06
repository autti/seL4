/*
 * Copyright 2017, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#ifndef __KERNEL_RISCV_TRAPS_H
#define __KERNEL_RISCV_TRAPS_H

#include <config.h>
#include <util.h>

static inline void arch_c_entry_hook(void)
{
}

static inline void arch_c_exit_hook(void)
{
}

void c_handle_syscall(word_t cptr, word_t msgInfo, word_t unused1, word_t unused2, word_t unused3, word_t unused4, word_t unused5, syscall_t syscall)
VISIBLE SECTION(".vectors.text");

void c_handle_interrupt(void)
VISIBLE SECTION(".vectors.text");

void c_handle_exception(void)
VISIBLE SECTION(".vectors.text");

void restore_user_context(void)
VISIBLE NORETURN SECTION(".vectors.text");

#endif /* __KERNEL_RISCV_TRAPS_H */
