/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <model/statedata.h>
#include <arch/kernel/traps.h>
#include <machine/debug.h>
#include <api/syscall.h>
#include <util.h>

#include <benchmark/benchmark_track.h>
#include <benchmark/benchmark_utilisation.h>

/** DONT_TRANSLATE */
void VISIBLE NORETURN restore_user_context(void)
{
    /* TODO: multicore - this is only added for future multicore support
     * doesn't do anything now
     */
    NODE_UNLOCK_IF_HELD;

    word_t cur_thread_reg = (word_t) NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers;

    c_exit_hook();

    asm volatile(
        "mv t0, %[cur_thread]       \n"
        "ld x1, (33*%[REGSIZE])(t0) \n"
        "csrw sstatus, x1\n"
        "ld ra, (1*%[REGSIZE])(t0)  \n"
        "ld sp, (2*%[REGSIZE])(t0)  \n"
        "ld gp, (3*%[REGSIZE])(t0)  \n"
        /* skip tp */
        /* skip x5/t0 */
        "ld t2, (7*%[REGSIZE])(t0)  \n"
        "ld s0, (8*%[REGSIZE])(t0)  \n"
        "ld s1, (9*%[REGSIZE])(t0)  \n"
        "ld a0, (10*%[REGSIZE])(t0) \n"
        "ld a1, (11*%[REGSIZE])(t0) \n"
        "ld a2, (12*%[REGSIZE])(t0) \n"
        "ld a3, (13*%[REGSIZE])(t0) \n"
        "ld a4, (14*%[REGSIZE])(t0) \n"
        "ld a5, (15*%[REGSIZE])(t0) \n"
        "ld a6, (16*%[REGSIZE])(t0) \n"
        "ld a7, (17*%[REGSIZE])(t0) \n"
        "ld s2, (18*%[REGSIZE])(t0) \n"
        "ld s3, (19*%[REGSIZE])(t0) \n"
        "ld s4, (20*%[REGSIZE])(t0) \n"
        "ld s5, (21*%[REGSIZE])(t0) \n"
        "ld s6, (22*%[REGSIZE])(t0) \n"
        "ld s7, (23*%[REGSIZE])(t0) \n"
        "ld s8, (24*%[REGSIZE])(t0) \n"
        "ld s9, (25*%[REGSIZE])(t0) \n"
        "ld s10, (26*%[REGSIZE])(t0)\n"
        "ld s11, (27*%[REGSIZE])(t0)\n"
        "ld t3, (28*%[REGSIZE])(t0) \n"
        "ld t4, (29*%[REGSIZE])(t0) \n"
        "ld t5, (30*%[REGSIZE])(t0) \n"
        "ld t6, (31*%[REGSIZE])(t0) \n"
        /* Get next restored tp */
        "ld t1, (4*%[REGSIZE])(t0)  \n"
        /* get restored tp */
        "add tp, t1, x0  \n"
        /* get sepc */
        "ld t1, (34*%[REGSIZE])(t0)\n"
        "csrw sepc, t1  \n"

        "ld t1, (6*%[REGSIZE])(t0) \n"
        "csrrw t0, sscratch, t0  \n"
        "sret"
        : /* no output */
        : [REGSIZE] "i" (sizeof(word_t)),
        [cur_thread] "r" (cur_thread_reg)
        : "memory"
    );

    UNREACHABLE();
}

void VISIBLE NORETURN
c_handle_interrupt(void)
{
    c_entry_hook();

    handleInterruptEntry();

    restore_user_context();
    UNREACHABLE();
}

void VISIBLE NORETURN
c_handle_exception(void)
{
    c_entry_hook();

    handle_exception();

    restore_user_context();
    UNREACHABLE();
}

void NORETURN
slowpath(syscall_t syscall)
{
    /* check for undefined syscall */
    if (unlikely(syscall < SYSCALL_MIN || syscall > SYSCALL_MAX)) {
        /* TODO: benchmarks - this is only added for future benchmark support
         * doesn't do anything now, and benchmarking support is currently broken,
         * and not tested.
         */
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_UnknownSyscall;
        /* ksKernelEntry.word word is already set to syscall */
#endif /* TRACK_KERNEL_ENTRIES */
        handleUnknownSyscall(syscall);
    } else {
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.is_fastpath = 0;
#endif /* TRACK KERNEL ENTRIES */
        handleSyscall(syscall);
    }

    restore_user_context();
    UNREACHABLE();
}

void VISIBLE NORETURN
c_handle_syscall(word_t cptr, word_t msgInfo, word_t unused1, word_t unused2, word_t unused3, word_t unused4, word_t unused5, syscall_t syscall)
{
    NODE_LOCK_SYS;

    c_entry_hook();

    /* TODO: benchmarks - this is only added for future benchmark support
     * doesn't do anything now, and benchmarking support is currently broken,
     * and not tested.
     */
#ifdef TRACK_KERNEL_ENTRIES
    benchmark_debug_syscall_start(cptr, msgInfo, syscall);
    ksKernelEntry.is_fastpath = 1;
#endif /* TRACK_KERNEL_ENTRIES */

#ifdef CONFIG_FASTPATH
    if (syscall == (syscall_t)SysCall) {
        fastpath_call(cptr, msgInfo);
        UNREACHABLE();
    } else if (syscall == (syscall_t)SysReplyRecv) {
        fastpath_reply_recv(cptr, msgInfo);
        UNREACHABLE();
    }
#endif /* CONFIG_FASTPATH */
    slowpath(syscall);
    UNREACHABLE();
}
