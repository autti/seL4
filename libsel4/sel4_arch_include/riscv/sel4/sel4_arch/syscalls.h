/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#ifndef __LIBSEL4_SEL4_ARCH_SYSCALLS_H
#define __LIBSEL4_SEL4_ARCH_SYSCALLS_H

#include <autoconf.h>
#include <sel4/arch/functions.h>
#include <sel4/types.h>

#define __SWINUM(x) ((x) & 0x00ffffff)

static inline void
seL4_Send(seL4_CPtr dest, seL4_MessageInfo_t msgInfo)
{
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    register seL4_Word info asm("a1") = msgInfo.words[0];

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2") = seL4_GetMR(0);
    register seL4_Word msg1 asm("a3") = seL4_GetMR(1);
    register seL4_Word msg2 asm("a4") = seL4_GetMR(2);
    register seL4_Word msg3 asm("a5") = seL4_GetMR(3);

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysSend;
    asm volatile ("ecall" : "+r"(destptr), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");
}

static inline void
seL4_SendWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo,
                 seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    register seL4_Word info asm("a1") = msgInfo.words[0];

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");
    register seL4_Word scno asm("a7") = seL4_SysSend;

    if (mr0 != (void *) 0  && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    /* Perform the system call. */
    asm volatile ("ecall" : "+r"(destptr), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");
}

static inline void
seL4_NBSend(seL4_CPtr dest, seL4_MessageInfo_t msgInfo)
{
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    register seL4_Word info asm("a1") = msgInfo.words[0];

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2") = seL4_GetMR(0);
    register seL4_Word msg1 asm("a3") = seL4_GetMR(1);
    register seL4_Word msg2 asm("a4") = seL4_GetMR(2);
    register seL4_Word msg3 asm("a5") = seL4_GetMR(3);

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysNBSend;
    asm volatile ("ecall" : "+r"(destptr), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");
}

static inline void
seL4_NBSendWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo,
                   seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    register seL4_Word info asm("a1") = msgInfo.words[0];

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");
    register seL4_Word scno asm("a7") = seL4_SysNBSend;

    if (mr0 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    /* Perform the system call. */
    asm volatile ("ecall" : "+r"(destptr), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");
}

static inline void
seL4_Reply(seL4_MessageInfo_t msgInfo)
{
    register seL4_Word info asm("a1") = msgInfo.words[0];

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2") = seL4_GetMR(0);
    register seL4_Word msg1 asm("a3") = seL4_GetMR(1);
    register seL4_Word msg2 asm("a4") = seL4_GetMR(2);
    register seL4_Word msg3 asm("a5") = seL4_GetMR(3);

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysReply;
    asm volatile ("ecall" : "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");
}

static inline void
seL4_ReplyWithMRs(seL4_MessageInfo_t msgInfo,
                  seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    register seL4_Word info asm("a1") = msgInfo.words[0];

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");
    register seL4_Word scno asm("a7") = seL4_SysReply;

    if (mr0 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    /* Perform the system call. */
    asm volatile ("ecall" : "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");
}

static inline void
seL4_Signal(seL4_CPtr dest)
{
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    register seL4_Word info asm("a1") = seL4_MessageInfo_new(0, 0, 0, 0).words[0];

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysSend;
    asm volatile ("ecall" : "+r"(destptr) : "r"(info), "r"(scno) : "memory");
}

static inline seL4_MessageInfo_t
seL4_Recv(seL4_CPtr src, seL4_Word* sender)
{
    register seL4_Word src_and_badge asm("a0") = (seL4_Word)src;
    register seL4_MessageInfo_t info asm("a1");

    /* Incoming message registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysRecv;
    asm volatile ("ecall" : "+r"(src_and_badge), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");

    /* Write the message back out to memory. */
    seL4_SetMR(0, msg0);
    seL4_SetMR(1, msg1);
    seL4_SetMR(2, msg2);
    seL4_SetMR(3, msg3);

    /* Return back sender and message information. */
    if (sender) {
        *sender = src_and_badge;
    }
    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline seL4_MessageInfo_t
seL4_RecvWithMRs(seL4_CPtr src, seL4_Word* sender,
                 seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    register seL4_Word src_and_badge asm("a0") = (seL4_Word)src;
    register seL4_MessageInfo_t info asm("a1");

    /* Incoming message registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysRecv;
    asm volatile ("ecall" : "+r"(src_and_badge) , "=r"(info.words[0]), "=r"(msg0), "=r"(msg1), "=r"(msg2), \
                  "=r"(msg3): "r"(scno) : "memory");

    /* Write the message back out to memory. */
    if (mr0 != (void *) 0) {
        *mr0 = msg0;
    }
    if (mr1 != (void *) 0) {
        *mr1 = msg1;
    }
    if (mr2 != (void *) 0) {
        *mr2 = msg2;
    }
    if (mr3 != (void *) 0) {
        *mr3 = msg3;
    }

    /* Return back sender and message information. */
    if (sender) {
        *sender = src_and_badge;
    }
    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline seL4_MessageInfo_t
seL4_NBRecv(seL4_CPtr src, seL4_Word* sender)
{
    register seL4_Word src_and_badge asm("a0") = (seL4_Word)src;
    register seL4_MessageInfo_t info asm("a1");

    /* Incoming message registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysNBRecv;
    asm volatile ("ecall" : "+r"(src_and_badge) , "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");

    /* Write the message back out to memory. */
    seL4_SetMR(0, msg0);
    seL4_SetMR(1, msg1);
    seL4_SetMR(2, msg2);
    seL4_SetMR(3, msg3);

    /* Return back sender and message information. */
    if (sender) {
        *sender = src_and_badge;
    }

    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline seL4_MessageInfo_t
seL4_Call(seL4_CPtr dest, seL4_MessageInfo_t msgInfo)
{
    register seL4_MessageInfo_t info asm("a1") = msgInfo;

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2") = seL4_GetMR(0);
    register seL4_Word msg1 asm("a3") = seL4_GetMR(1);
    register seL4_Word msg2 asm("a4") = seL4_GetMR(2);
    register seL4_Word msg3 asm("a5") = seL4_GetMR(3);

    /* Perform the system call. */
    register seL4_Word scno asm("a7") = seL4_SysCall;
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    asm volatile ("ecall" : "+r"(destptr), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) :  "memory");

    /* Write out the data back to memory. */
    seL4_SetMR(0, msg0);
    seL4_SetMR(1, msg1);
    seL4_SetMR(2, msg2);
    seL4_SetMR(3, msg3);

    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline seL4_MessageInfo_t
seL4_CallWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo,
                 seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    register seL4_Word destptr asm("a0") = (seL4_Word)dest;
    register seL4_MessageInfo_t info asm("a1") = msgInfo;

    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");
    register seL4_Word scno asm("a7") = seL4_SysCall;

    /* Load beginning of the message into registers. */
    if (mr0 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    /* Perform the system call. */
    asm volatile ("ecall" : "+r"(destptr), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3) : "r"(scno) : "memory");

    /* Write out the data back to memory. */
    if (mr0 != (void *) 0) {
        *mr0 = msg0;
    }
    if (mr1 != (void *) 0) {
        *mr1 = msg1;
    }
    if (mr2 != (void *) 0) {
        *mr2 = msg2;
    }
    if (mr3 != (void *) 0) {
        *mr3 = msg3;
    }

    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline seL4_MessageInfo_t
seL4_ReplyRecv(seL4_CPtr src, seL4_MessageInfo_t msgInfo, seL4_Word *sender)
{
    register seL4_Word src_and_badge asm("a0") = (seL4_Word)src;
    register seL4_MessageInfo_t info asm("a1") = msgInfo;

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2") = seL4_GetMR(0);
    register seL4_Word msg1 asm("a3") = seL4_GetMR(1);
    register seL4_Word msg2 asm("a4") = seL4_GetMR(2);
    register seL4_Word msg3 asm("a5") = seL4_GetMR(3);

    /* Perform the syscall. */
    register seL4_Word scno asm("a7") = seL4_SysReplyRecv;
    asm volatile ("ecall" : "+r"(src_and_badge), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");

    /* Write the message back out to memory. */
    seL4_SetMR(0, msg0);
    seL4_SetMR(1, msg1);
    seL4_SetMR(2, msg2);
    seL4_SetMR(3, msg3);

    /* Return back sender and message information. */
    if (sender) {
        *sender = src_and_badge;
    }
    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline seL4_MessageInfo_t
seL4_ReplyRecvWithMRs(seL4_CPtr src, seL4_MessageInfo_t msgInfo, seL4_Word *sender,
                      seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    register seL4_Word src_and_badge asm("a0") = (seL4_Word)src;
    register seL4_MessageInfo_t info asm("a1") = msgInfo;

    /* Load beginning of the message into registers. */
    register seL4_Word msg0 asm("a2");
    register seL4_Word msg1 asm("a3");
    register seL4_Word msg2 asm("a4");
    register seL4_Word msg3 asm("a5");
    register seL4_Word scno asm("a7") = seL4_SysReplyRecv;

    if (mr0 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != (void *) 0 && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    /* Perform the syscall. */
    asm volatile ("ecall" : "+r"(src_and_badge), "+r"(info), "+r"(msg0), "+r"(msg1), "+r"(msg2), \
                  "+r"(msg3): "r"(scno) : "memory");

    /* Write out the data back to memory. */
    if (mr0 != (void *) 0) {
        *mr0 = msg0;
    }
    if (mr1 != (void *) 0) {
        *mr1 = msg1;
    }
    if (mr2 != (void *) 0) {
        *mr2 = msg2;
    }
    if (mr3 != (void *) 0) {
        *mr3 = msg3;
    }

    /* Return back sender and message information. */
    if (sender) {
        *sender = src_and_badge;
    }
    return (seL4_MessageInfo_t) {
        .words = {info.words[0]}
    };
}

static inline void
seL4_Yield(void)
{
    register seL4_Word scno asm("a7") = seL4_SysYield;
    asm volatile ("ecall" :: "r"(scno));
}

#ifdef SEL4_DEBUG_KERNEL
static inline void
seL4_DebugPutChar(char c)
{
    register seL4_Word arg1 asm("a0") = c;
    register seL4_Word scno asm("a7") = seL4_SysDebugPutChar;
    asm volatile ("ecall" :: "r"(arg1), "r"(scno) : "memory");
}

char *strcpy(char *, const char *);
LIBSEL4_INLINE_FUNC void
seL4_DebugNameThread(seL4_CPtr tcb, const char *name)
{
    /* TODO */
}
#endif

#ifdef SEL4_DEBUG_KERNEL
static inline void
seL4_DebugHalt(void)
{
    register seL4_Word scno asm("a7") = seL4_SysDebugHalt;
    asm volatile ("ecall" :: "r"(scno) : "memory");
}
#endif

#ifdef SEL4_DEBUG_KERNEL
static inline void
seL4_DebugSnapshot(void)
{
    register seL4_Word scno asm("a7") = seL4_SysDebugSnapshot;
    asm volatile ("ecall" ::"r"(scno) : "memory");
}
#endif

#ifdef SEL4_DEBUG_KERNEL
static inline seL4_Uint32
seL4_DebugCapIdentify(seL4_CPtr cap)
{
    register seL4_Word arg1 asm("a0") = cap;
    register seL4_Word scno asm("a7") = seL4_SysDebugCapIdentify;
    asm volatile ("ecall" : "+r"(arg1) : "r"(scno));
    return (seL4_Uint32)arg1;
}
#endif

#ifdef SEL4_DANGEROUS_CODE_INJECTION_KERNEL
static inline void
seL4_DebugRun(void (* userfn) (void *), void* userarg)
{
    register seL4_Word arg1 asm("a0") = (seL4_Word)userfn;
    register seL4_Word arg2 asm("a1") = (seL4_Word)userarg;
    register seL4_Word scno asm("a7") = seL4_SysDebugRun;
    asm volatile ("ecall" : "+r"(arg1) : "r"(arg2), "r"(scno));
}
#endif

#ifdef CONFIG_BENCHMARK
/* TODO */
#endif /* CONFIG_BENCHMARK */

#undef __SWINUM

#endif /* __LIBSEL4_SEL4_ARCH_SYSCALLS_H */
