/* SPDX-License-Identifier: Apache-2.0 */
#ifndef __DAP_PORT_H__
#define __DAP_PORT_H__

/* DAP_config.h is included first. A board may provide the optional hooks below.
 * No OS or board header is included by the command core itself.
 *
 * DAP_PORT_DELAY_MS(ms) / DAP_PORT_DELAY_US(us): command delays, in wall-time units.
 * DAP_PORT_PIN_DELAY_SLOW(count) / DAP_PORT_PIN_DELAY_FAST(): bit-loop delays.
 *   count is an iteration count, NOT microseconds; calibrate DELAY_SLOW_CYCLES.
 * DAP_PORT_SWJ_CLOCK(hz): configure the bit backend, return 0 on success.
 *   A custom backend owns its timing state; the built-in SW_DP/JTAG_DP backend
 *   should normally keep the default Set_Clock_Delay implementation.
 * DAP_PORT_SWJ_PINS(value, select, wait_us): return sampled physical pin bitmap.
 *   Custom backends own pin mux, direction and wait limits.
 * DAP_ATOMIC_COMMANDS: advertised capability only; defaults to official value 1.
 *   The transport must implement queue/execute semantics before advertising it.
 */
#ifndef DAP_ATOMIC_COMMANDS
#define DAP_ATOMIC_COMMANDS 1
#endif
#if (DAP_ATOMIC_COMMANDS != 0) && (DAP_ATOMIC_COMMANDS != 1)
#error "DAP_ATOMIC_COMMANDS must be 0 or 1"
#endif

#if defined(__riscv)
/* CMSIS compiler headers target Arm. The RISC-V command/bit engines only need
 * these compiler attributes and NOP, not Arm CPU intrinsics. */
#if !defined(__GNUC__) && !defined(__clang__)
#error "RISC-V CMSIS-DAP port requires a GNU-compatible compiler"
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE static inline __attribute__((always_inline))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __NOP
#define __NOP() __asm__ volatile ("nop")
#endif
#else
/* Existing Arm builds continue to use their original CMSIS compiler support. */
#include "cmsis_compiler.h"
#endif

#endif /* __DAP_PORT_H__ */
