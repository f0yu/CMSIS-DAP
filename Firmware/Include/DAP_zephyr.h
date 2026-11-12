/* SPDX-License-Identifier: Apache-2.0 */
#ifndef __DAP_ZEPHYR_H__
#define __DAP_ZEPHYR_H__

/* Optional: include from a Zephyr board's DAP_config.h, on Arm OR RISC-V.
 * OS selection is independent of CPU architecture and of GPIO/SPI ownership.
 * Command delays use time units; do not replace bit-loop counts with us.
 */
#if !defined(__ZEPHYR__)
#error "Include DAP_zephyr.h only from a Zephyr application configuration"
#endif
#include <zephyr/kernel.h>
#ifndef DAP_PORT_DELAY_MS
#define DAP_PORT_DELAY_MS(ms) k_msleep(ms)
#endif
#ifndef DAP_PORT_DELAY_US
#define DAP_PORT_DELAY_US(us) k_busy_wait(us)
#endif

#endif /* __DAP_ZEPHYR_H__ */
