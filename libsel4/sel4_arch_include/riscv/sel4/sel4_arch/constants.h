/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#ifndef __LIBSEL4_SEL4_ARCH_CONSTANTS_H
#define __LIBSEL4_SEL4_ARCH_CONSTANTS_H

#include <autoconf.h>

#define seL4_WordBits           64
#define seL4_PageBits           12
#define seL4_SlotBits           5
#define seL4_TCBBits            11
#define seL4_EndpointBits       4
#define seL4_NotificationBits   5
#define seL4_PageTableBits      12
#define seL4_PageDirBits        12
#define seL4_LVL2PageTableBits  12
#define seL4_IOPageTableBits    12
#define seL4_LargePageBits      21
#define seL4_HugePageBits       30
#define seL4_ASIDPoolBits       12

/* Untyped size limits */
#define seL4_MinUntypedBits 4
#define seL4_MaxUntypedBits 29

enum {
    seL4_VMFault_IP,
    seL4_VMFault_Addr,
    seL4_VMFault_FSR,
    seL4_VMFault_Length,
    //SEL4_FORCE_LONG_ENUM(seL4_VMFault_Msg),
} seL4_VMFault_Msg;

enum {
    seL4_UnknownSyscall_FaultIP,
    seL4_UnknownSyscall_SP,
    seL4_UnknownSyscall_RA,
    seL4_UnknownSyscall_A0,
    seL4_UnknownSyscall_A1,
    seL4_UnknownSyscall_A2,
    seL4_UnknownSyscall_A3,
    seL4_UnknownSyscall_A4,
    seL4_UnknownSyscall_A5,
    seL4_UnknownSyscall_A6,
    seL4_UnknownSyscall_Syscall,
    seL4_UnknownSyscall_Length,
    //SEL4_FORCE_LONG_ENUM(seL4_UnknownSyscall_Msg)
} seL4_UnknownSyscall_Msg;

enum {
    seL4_UserException_FaultIP,
    seL4_UserException_SP,
    seL4_UserException_FLAGS,
    seL4_UserException_Number,
    seL4_UserException_Code,
    seL4_UserException_Length,
    //SEL4_FORCE_LONG_ENUM(seL4_UserException_Msg)
} seL4_UserException_Msg;


#endif
