/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <machine/io.h>
#include <kernel/vspace.h>
#include <arch/machine.h>
#include <arch/kernel/vspace.h>
#include <plat/machine.h>
#include <arch/linker.h>
#include <plat/machine/devices.h>
#include <plat/machine/hardware.h>
#include <arch/sbi.h>

/* Available physical memory regions on platform (RAM minus kernel image). */
/* NOTE: Regions are not allowed to be adjacent! */

const p_region_t BOOT_RODATA avail_p_regs[] = {
    /* 128 MiB of memory minus kernel image at its beginning */
    { .start = 0x0000000080800000, .end = 0x0000000090000000 }
};

BOOT_CODE int get_num_avail_p_regs(void)
{
    return sizeof(avail_p_regs) / sizeof(p_region_t);
}

BOOT_CODE p_region_t get_avail_p_reg(unsigned int i)
{
    return avail_p_regs[i];
}


BOOT_CODE int get_num_dev_p_regs(void)
{
    return 0;
}

BOOT_CODE p_region_t get_dev_p_reg(unsigned int i)
{
}

/**
   DONT_TRANSLATE
 */
interrupt_t
getActiveIRQ(void)
{

    uint64_t temp = 0;
    asm volatile ("csrr %0, scause":"=r" (temp)::);

    if (!(temp & 0x8000000000000000UL)) {
        return irqInvalid;
    }

    return (temp & 0xf);
}

/* Check for pending IRQ */
bool_t isIRQPending(void)
{
    return (getActiveIRQ() != irqInvalid);
    /* FIXME: IRQ Pending not implemented now */
}

/* Enable or disable irq according to the 'disable' flag. */
/**
   DONT_TRANSLATE
*/
void
maskInterrupt(bool_t disable, interrupt_t irq)
{
    if (disable) {
        clear_csr(sie, irq);
    } else {
        set_csr(sie, irq);
    }
}

/* Determine if the given IRQ should be reserved by the kernel. */
bool_t CONST
isReservedIRQ(irq_t irq)
{
    printf("isReservedIRQ \n");
    return false;
}

/* Handle a platform-reserved IRQ. */
void
handleReservedIRQ(irq_t irq)
{
    printf("handleReservedIRQ \n");
}

void
ackInterrupt(irq_t irq)
{
    clear_csr(sip, irq);
}

static unsigned long timebase;

static inline uint64_t get_cycles(void)
{
    uint64_t n;
    __asm__ __volatile__ (
        "rdtime %0"
        : "=r" (n));
    return n;
}

static inline int read_current_timer(unsigned long *timer_val)
{
    *timer_val = get_cycles();
    return 0;
}

void
resetTimer(void)
{
    /* Timer resets automatically */
    //sbi_set_timer(get_cycles() + (0xfffff / 10));
    //uint32_t timer_val = read_csr(stime);
    /* 10ms? */
    //write_csr(stimecmp, timer_val + TIMER_TICK_NS);
}

/**
   DONT_TRANSLATE
 */
BOOT_CODE void
initTimer(void)
{
    //timebase = sbi_timebase();
    timebase = 0;

    //printf("%d\n", get_cycles());
    //sbi_set_timer(get_cycles() + 0xfffff);
    //sbi_set_timer(csr_read(stime) + 0xffffff);
    /* 10ms? */
    //write_csr(stimecmp, timer_val + TIMER_TICK_NS);

    /* Enable timer interrupt */
    //set_csr(sie, 0x20);
}

static void invalidateL2(void)
{
}

static void finaliseL2Op(void)
{
}

void plat_cleanL2Range(paddr_t start, paddr_t end)
{
}
void plat_invalidateL2Range(paddr_t start, paddr_t end)
{
}

void plat_cleanInvalidateL2Range(paddr_t start, paddr_t end)
{
}

/**
   DONT_TRANSLATE
 */
BOOT_CODE void
initL2Cache(void)
{
}

/**
   DONT_TRANSLATE
 */
BOOT_CODE void
initIRQController(void)
{
    /* Do nothing */
    printf("Init IRQ!! \n");
}

void
handleSpuriousIRQ(void)
{
    /* Do nothing */
    printf("Superior IRQ!! \n");
}

