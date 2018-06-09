/*-
 * Copyright (c) 2018 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/console.h>
#include <machine/frame.h>
#include <machine/cpuregs.h>
#include <machine/cpufunc.h>

#include <mips/microchip/pic32mzda.h>

#define	CPU_FREQ	200000000
void app_init(void);

PIC32_DEVCFG (
	DEVCFG0_UNUSED |
	DEVCFG0_BOOTISA_MIPS32,
	DEVCFG1_UNUSED |
	DEVCFG1_FNOSC_SPLL |
	DEVCFG1_POSCMOD_HS_OSC |
	DEVCFG1_FCKSM_CKS_EN_M_EN |
	DEVCFG1_IESO,
	DEVCFG2_UNUSED |
	DEVCFG2_FPLLIDIV(3) |
	DEVCFG2_FPLLRNG_5_10 |
	DEVCFG2_FPLLMULT(50) |
	DEVCFG2_FPLLODIV_2 |
	DEVCFG2_UPLLFSEL_24MHZ,
	DEVCFG3_UNUSED |
	DEVCFG3_FETHIO |
	DEVCFG3_USERID(0xffff)
);

/* Software contexts */
static struct pic32_uart_softc uart_sc;
static struct pic32_port_softc port_sc;
static struct pic32_pps_softc pps_sc;
static struct pic32_syscfg_softc syscfg_sc;

static void
uart_putchar(int c, void *arg)
{
	struct pic32_uart_softc *sc;

	sc = arg;

	if (c == '\n')
		pic32_putc(sc, '\r');

	pic32_putc(sc, c);
}

static void
app_ports_init(struct pic32_port_softc *sc)
{

	/* UART2 digital */
	pic32_port_ansel(&port_sc, PORT_B, 14, 1);
	pic32_port_ansel(&port_sc, PORT_B, 15, 1);

	pic32_pps_write(&pps_sc, PPS_U2RXR, IS2_RPB0);
	pic32_pps_write(&pps_sc, PPS_RPG9R, OS3_U2TX);
}

void
app_init(void)
{

	pic32_port_init(&port_sc, PORTS_BASE);
	pic32_pps_init(&pps_sc, PPS_BASE);
	pic32_syscfg_init(&syscfg_sc, SYSCFG_BASE);

	app_ports_init(&port_sc);

	pic32_uart_init(&uart_sc, UART2_BASE, 115200, CPU_FREQ, 2);
	console_register(uart_putchar, (void *)&uart_sc);

	printf("\n\n\n");
	printf("osfive initialized: jumping to U-Boot...\n");
}
