APP =		pic32mzdask-uboot
ARCH =		mips

CC =		${CROSS_COMPILE}gcc
LD =		${CROSS_COMPILE}ld
OBJCOPY =	${CROSS_COMPILE}objcopy

LDSCRIPT =	${.CURDIR}/ldscript

OBJECTS =	main.o						\
		osfive/sys/mips/microchip/pic32_uart.o		\
		osfive/sys/mips/microchip/pic32_port.o		\
		osfive/sys/mips/microchip/pic32_pps.o		\
		osfive/sys/mips/microchip/pic32_syscfg.o	\
		osfive/sys/kern/subr_prf.o			\
		osfive/sys/kern/subr_console.o			\
		osfive/lib/libc/stdio/printf.o			\
		osfive/lib/libc/string/strlen.o			\
		start.o

CFLAGS =	-march=mips32r2 -EL -msoft-float				\
		-nostdlib -mno-abicalls -O -fno-pic -fno-builtin-printf		\
		-O -pipe -g -nostdinc -fno-omit-frame-pointer			\
		-fno-optimize-sibling-calls -ffreestanding -fwrapv		\
		-fdiagnostics-show-option -fms-extensions -finline-limit=8000	\
		-Wall -Wredundant-decls -Wnested-externs -Wstrict-prototypes	\
		-Wmissing-prototypes -Wpointer-arith -Winline -Wcast-qual	\
		-Wundef -Wno-pointer-sign -Wno-format -Wmissing-include-dirs	\
		-Wno-unknown-pragmas -Werror

all: compile link srec

clean:
	rm -f ${OBJECTS:M*} ${APP}.elf ${APP}.srec

.include "osfive/mk/user.mk"
.include "osfive/mk/compile.mk"
.include "osfive/mk/link.mk"
