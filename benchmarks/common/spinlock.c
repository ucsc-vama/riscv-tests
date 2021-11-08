
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */


#include "spinlock.h"

/*
 * Simple spin lock operations.  These provide no fairness guarantees.
 */


#define arch_spin_is_locked(x)	(READ_ONCE((x)->lock) != 0)

void arch_spin_unlock(arch_spinlock_t *lock)
{
	smp_store_release(&lock->lock, 0);
}

int arch_spin_trylock(arch_spinlock_t *lock)
{
	int tmp = 1, busy;

	__asm__ __volatile__ (
		"	amoswap.w %0, %2, %1\n"
		RISCV_ACQUIRE_BARRIER
		: "=r" (busy), "+A" (lock->lock)
		: "r" (tmp)
		: "memory");

	return !busy;
}

void arch_spin_lock(arch_spinlock_t *lock)
{
	while (1) {
		if (arch_spin_is_locked(lock))
			continue;

		if (arch_spin_trylock(lock))
			break;
	}
}
