/*
 * This file is part of "Phoenix Game Engine".
 *
 * Copyright (C) 2008 Phoenix Game Engine
 * Copyright (C) 2008 InsertWittyName <tias_dp@hotmail.com>
 * Copyright (C) 2008 MK2k <pge@mk2k.net>
 *
 * Phoenix Game Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Phoenix Game Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Phoenix Game Engine.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <pspkernel.h>
#include <psppower.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <psputility.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>


#include <Aurora/Utils/pge.h>
//#include "support/pgesupportprx.h"

#ifdef __PSP__
PSP_MODULE_INFO("Phoenix Game Engine", PSP_MODULE_USER, 1, PGE_VERSION);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER|PSP_THREAD_ATTR_VFPU);
#endif

static int running = 1;

void pgeExit(void) {
    running = 0;

    sceKernelExitGame();
}

void pgeDelay(unsigned int delay) {
    sceKernelDelayThread(delay);
}

void *pgeMalloc(int size) {
    void *ptr = malloc(size);
    return ptr;
}

void pgeFree(void *ptr) {
    if (ptr != NULL)
        free(ptr);
}

void *pgeRealloc(void *ptr, int size) {
    return realloc(ptr, size);
}
