APP =		pic32mzdask-uboot
MACHINE =	mips

CC =		${CROSS_COMPILE}gcc
LD =		${CROSS_COMPILE}ld
OBJCOPY =	${CROSS_COMPILE}objcopy

OBJDIR =	obj
LDSCRIPT =	${CURDIR}/ldscript

OBJECTS =	main.o						\
		osfive/sys/mips/microchip/pic32_uart.o		\
		osfive/sys/mips/microchip/pic32_port.o		\
		osfive/sys/mips/microchip/pic32_pps.o		\
		osfive/sys/mips/microchip/pic32_syscfg.o	\
		start.o

CFLAGS =	-march=mips32r2 -EL -msoft-float -nostdlib	\
		-mno-abicalls -O -fno-pic -fno-builtin-printf	\
		-O -pipe -g -nostdinc -fno-omit-frame-pointer	\
		-fno-optimize-sibling-calls -ffreestanding	\
		-fwrapv	-fdiagnostics-show-option		\
		-fms-extensions -finline-limit=8000 -Wall	\
		-Wredundant-decls -Wnested-externs		\
		-Wstrict-prototypes -Wmissing-prototypes	\
		-Wpointer-arith -Winline -Wcast-qual -Wundef	\
		-Wno-pointer-sign -Wno-format			\
		-Wmissing-include-dirs -Wno-unknown-pragmas	\
		-Werror -D__mips_o32

KERNEL =
LIBRARIES = libc libc_quad

all:	${OBJDIR}/${APP}.srec

clean:
	@rm -f ${OBJECTS} ${OBJDIR}/${APP}.srec

include osfive/lib/libc/Makefile.inc
include osfive/mk/default.mk
