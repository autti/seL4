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

#ifndef __ARCH_MACHINE_REGISTERSET_H
#define __ARCH_MACHINE_REGISTERSET_H

#include "hardware.h"

#define PT_SP               (2  * 8)
#define PT_A0               (10 * 8)

#define SSTATUS_FS 0x00006000

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <util.h>
#include <arch/types.h>

enum _register {

    ra = 1, LR = 1,

    sp = 2, SP = 2,
    gp = 3,
    tp = 4,

    t0 = 5,
    t1 = 6,
    t2 = 7,
    s0 = 8,
    s1 = 9,

    /* x10-x17 > a0-a7 */
    a0 = 10, capRegister = 10, badgeRegister = 10,
    a1 = 11, msgInfoRegister = 11,
    a2 = 12,
    a3 = 13,
    a4 = 14,
    a5 = 15,
    a6 = 16,
    a7 = 17,

    s2 = 18,
    s3 = 19,
    s4 = 20,
    s5 = 21,
    s6 = 22,
    s7 = 23,
    s8 = 24,
    s9 = 25,
    s10 = 26,
    s11 = 27,

    t3 = 28,
    t4 = 29,
    t5 = 30,
    t6 = 31,

    /* End of GP registers, the following are additional kernel-saved state. */
    SCAUSE,
    SSTATUS,
    SEPC,

    /* TODO: add other user-level CSRs if needed (i.e. to avoid channels) */

    n_contextRegisters
};

typedef uint64_t register_t;

enum messageSizes {
    n_msgRegisters = 4,
    n_frameRegisters = 17,
    n_gpRegisters = 0,
    n_exceptionMessage = 3,
    n_syscallMessage = 10
};

extern const register_t msgRegisters[] VISIBLE;
extern const register_t frameRegisters[] VISIBLE;
extern const register_t gpRegisters[] VISIBLE;
extern const register_t exceptionMessage[] VISIBLE;
extern const register_t syscallMessage[] VISIBLE;

struct user_context {
    word_t registers[n_contextRegisters];
};
typedef struct user_context user_context_t;

static inline void Arch_initContext(user_context_t* context)
{
    /* Enable floating point for new threads (discarded if HW doesn't support it)
     * otherwise, a FP exception will be triggered
     */
    context->registers[SSTATUS] = SSTATUS_FS;
}

static inline word_t CONST
sanitiseRegister(register_t reg, word_t v, void *thread)
{
    /* FIXME */
    return v;
}


#define EXCEPTION_MESSAGE \
 {\
    [seL4_UserException_FaultIP] = SEPC,\
    [seL4_UserException_SP] = SP,\
    [seL4_UserException_Number] = a7,\
 }

#define SYSCALL_MESSAGE \
{\
    [seL4_UnknownSyscall_FaultIP] = SEPC,\
    [seL4_UnknownSyscall_SP] = SP,\
    [seL4_UnknownSyscall_RA] = LR,\
    [seL4_UnknownSyscall_A0] = a0,\
    [seL4_UnknownSyscall_A1] = a1,\
    [seL4_UnknownSyscall_A2] = a2,\
    [seL4_UnknownSyscall_A3] = a3,\
    [seL4_UnknownSyscall_A4] = a4,\
    [seL4_UnknownSyscall_A5] = a5,\
    [seL4_UnknownSyscall_A6] = a6,\
}

#endif /* __ASSEMBLER__ */

#endif /* !__ARCH_MACHINE_REGISTERSET_H */
