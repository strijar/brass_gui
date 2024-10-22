/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <fcntl.h>

void vt_disable() {
    int vt = open("/dev/tty1", O_RDWR);

    if (vt > 0) {
        ioctl(vt, KDSETMODE, KD_GRAPHICS);
        close(vt);
    }
}

void vt_enable() {
    int vt = open("/dev/tty1", O_RDWR);

    if (vt > 0) {
        ioctl(vt, KDSETMODE, KD_TEXT);
        close(vt);
    }
}
