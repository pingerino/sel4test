/*
 * Copyright 2018, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */
#include "../../test.h"

#include <platsupport/plat/clock.h>
#include <sel4platsupport/io.h>
#include <utils/zf_log.h>
#include <platsupport/plat/serial.h>

#if defined(CONFIG_PLAT_EXYNOS5422)
void
plat_init(driver_env_t env)
{
    int error;
    ps_io_ops_t io_ops = {};
    clock_sys_t clock = {};
    clk_t *clk;

    error = sel4platsupport_new_io_mapper(env->vspace, env->vka, &io_ops.io_mapper);
    if (error != 0) {
        ZF_LOGF("Failed to initialise IO mapper");
    }

    error = clock_sys_init(&io_ops, &clock);
    if (error != 0) {
        ZF_LOGF("Failed to initalise clock");
    }

    clk = clk_get_clock(&clock, CLK_UART2);
    if (clk == NULL) {
        ZF_LOGF("Failed to get clock");
    }

    clk_set_freq(clk, UART_DEFAULT_FIN);
}
#endif
