# pic32mzdask-uboot
1st stage bootloader for PIC32MZDA Starter Kit

This application loads U-Boot on PIC32MZDA Starter Kit

UART baud rate: 115200

### Build under Linux

    $ export CROSS_COMPILE=mips-linux-gnu-
    $ git clone --recursive https://github.com/osfive/pic32mzdask-uboot
    $ cd pic32mzdask-uboot
    $ bmake

### Build under FreeBSD

    $ setenv CROSS_COMPILE mips-unknown-freebsd11.1-
    $ git clone --recursive https://github.com/osfive/pic32mzdask-uboot
    $ cd pic32mzdask-uboot
    $ make

### Assemble this app and U-Boot to a single file
    $ srec_cat pic32mzdask-uboot.srec /path/to/u-boot.srec > flash.srec
