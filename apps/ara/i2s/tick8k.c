/**
* Copyright (c) 2016 Google Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its
* contributors may be used to endorse or promote products derived from this
* software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <nuttx/util.h>
#include <stdlib.h>
#include "tick8k.h"

/* 8 Khz sample period, 16bit, 1 channel, signed PCM data
 * android tick sound
  */

#ifdef ENABLE_TICK_SAMPLE

int16_t sample_buffer[] = {
0x4A00, 0x6A00, 0xA7FF, 0x80FF,
0x9E00, 0x5001, 0x30FF, 0x43FE,
0x66F8, 0x34F0, 0x6EF8, 0xC9F7,
0xBCF5, 0xF1F6, 0x07EE, 0xFEED,
0xF5F8, 0x1C00, 0x7603, 0x8005,
0xB9F9, 0x5DF3, 0x28F7, 0x24F9,
0x31FF, 0xF503, 0xF4FC, 0x7EFD,
0xC404, 0xE901, 0xC70A, 0xA206,
0x66FE, 0x1C03, 0xCCFD, 0x8E02,
0x6106, 0x1507, 0xAE02, 0x0F06,
0x710B, 0x210A, 0x1F11, 0x610B,
0xEE00, 0xB205, 0x3CFD, 0xF403,
0xD608, 0x5906, 0x0907, 0x9806,
0xAC05, 0xCAFF, 0xE905, 0x3600,
0xBAFD, 0x2D02, 0xD4FD, 0x61FF,
0x0A01, 0x1BFD, 0x97FF, 0xF1FF,
0x6AFF, 0xE4FC, 0xE2FF, 0xBAFB,
0xECFA, 0x48FF, 0xB7FB, 0x9DFE,
0xF0FF, 0x67FE, 0xDBFF, 0x1200,
0x60FE, 0xE7FD, 0x18FE, 0x54FD,
0x6EFE, 0x0501, 0x4DFF, 0x2E00,
0x1600, 0x1CFF, 0xB8FF, 0xB100,
0x2400, 0xD1FF, 0xDCFF, 0xFBFE,
0x3500, 0x5401, 0xB900, 0x6601,
0x4201, 0x8200, 0x1801, 0xF800,
0x8400, 0xAA00, 0x4B00, 0x6600,
0x6801, 0x7501, 0xAE01, 0x4201,
0x7900, 0x5E00, 0x7000, 0x9900,
0x5200, 0x3000, 0x1B00, 0xEDFF,
0x5400, 0x3800, 0x6900, 0x3E00,
0xC1FF, 0xB1FF, 0xB9FF, 0xA4FF,
0xA1FF, 0xB8FF, 0x8DFF, 0xD0FF,
0x1E00, 0xBBFF, 0x1300, 0xAFFF,
0x6BFF, 0xB0FF, 0x85FF, 0xB0FF,
0xCDFF, 0xC5FF, 0xBFFF, 0xD6FF,
0xECFF, 0xCDFF, 0xEAFF, 0xC9FF,
0xABFF, 0xDBFF, 0xC0FF, 0xCEFF,
0xE2FF, 0xFCFF, 0xE6FF, 0x1C00,
0x1400, 0xEDFF, 0x0B00, 0xE8FF,
0xE7FF, 0x1900, 0x0000, 0x1600,
0x2200, 0x1100, 0x1600, 0x1C00,
0x1000, 0xFBFF, 0x0700, 0xF6FF,
0xFCFF, 0x0300, 0x0200, 0xFDFF,
0xFFFF, 0xFAFF, 0xFEFF, 0x0100,
0xEEFF, 0xDEFF, 0xE8FF, 0xD9FF,
0xE6FF, 0xF5FF, 0xE9FF, 0xEBFF,
0xECFF, 0xE4FF, 0xE3FF, 0xE4FF,
0xDDFF, 0xDDFF, 0xDCFF, 0xDCFF,
0xE9FF, 0xE8FF, 0xE2FF, 0xDFFF,
0xE4FF, 0xE1FF, 0xE1FF, 0xE4FF,
0xDCFF, 0xDBFF, 0xE1FF, 0xE3FF,
0xE7FF, 0xE8FF, 0xEEFF, 0xECFF,
0xE6FF, 0xE9FF, 0xE8FF, 0xE9FF,
0xE7FF, 0xEAFF, 0xEDFF, 0xF1FF,
0xEEFF, 0xEDFF, 0xF3FF, 0xEEFF,
0xEEFF, 0xF0FF, 0xEDFF, 0xEEFF,
0xECFF, 0xEEFF, 0xEEFF, 0xEFFF,
0xF1FF, 0xEEFF, 0xEEFF, 0xEFFF,
0xE8FF, 0xE7FF, 0xF2FF, 0xF1FF,
0xEBFF, 0xEFFF, 0xEDFF, 0xEEFF,
0xEDFF, 0xEEFF, 0xEEFF, 0xEBFF,
0xF0FF, 0xF1FF, 0xEAFF, 0xECFF,
0xF0FF, 0xEEFF, 0xEDFF, 0xEFFF,
0xF0FF, 0xF1FF, 0xEDFF, 0xEEFF,
0xEEFF, 0xEBFF, 0xF3FF, 0xF5FF,
0xEBFF, 0xF0FF, 0xF4FF, 0xF1FF,
0xF2FF, 0xF1FF, 0xF0FF, 0xF4FF,
0xEFFF, 0xEEFF, 0xF6FF, 0xF6FF,
0xEDFF, 0xEEFF, 0xF7FF, 0xF5FF,
0xF1FF, 0xF2FF, 0xF4FF, 0xF4FF,
0xF3FF, 0xF5FF, 0xF2FF, 0xF0FF,
0xF6FF, 0xF5FF, 0xF1FF, 0xF2FF,
0xF5FF, 0xF4FF, 0xF4FF, 0xF4FF,
0xF4FF, 0xF6FF, 0xF3FF, 0xF3FF,
0xF6FF, 0xF4FF, 0xF5FF, 0xF8FF,
0xF5FF, 0xFBFF, 0xF5FF, 0xF7FF,
0xF9FF, 0xF8FF, 0xF4FF, 0xF7FF,
0xF6FF, 0xF6FF, 0xF9FF, 0xFCFF,
0xF4FF, 0xF7FF, 0xFAFF, 0xF8FF,
0xF9FF, 0xF5FF, 0xFAFF, 0xFFFF,
0xF1FF, 0xF2FF, 0x0200, 0xFDFF,
0xF8FF, 0xF9FF, 0xF9FF, 0xFDFF,
0xF6FF, 0xF5FF, 0xFFFF, 0xFEFF,
0xF7FF, 0xF9FF, 0xFCFF, 0xFCFF,
0xFAFF, 0xFAFF, 0xFCFF, 0xFCFF,
0xF9FF, 0xF7FF, 0xFEFF, 0xFFFF,
0xF9FF, 0xFBFF, 0xFDFF, 0xFDFF,
0xFBFF, 0xFCFF, 0xFDFF, 0xFBFF,
0xFDFF, 0xFDFF, 0xFBFF, 0xFBFF,
0xFFFF, 0xFDFF, 0xFBFF, 0xFEFF,
0xFCFF, 0xFDFF, 0xFEFF, 0xFCFF,
0xFDFF, 0xFFFF, 0xFDFF, 0xFAFF,
0x0000, 0xFFFF, 0xFBFF, 0xFFFF,
0xFDFF, 0xFEFF, 0xFEFF, 0xFEFF,
0xFFFF, 0x0000, 0xFCFF, 0xFCFF,
0x0000, 0xFEFF, 0xFDFF, 0xFEFF,
0xFEFF, 0xFDFF, 0xFFFF, 0x0100,
0xFDFF, 0xFDFF, 0x0100, 0x0100,
0xFDFF, 0x0000, 0x0000, 0xFDFF,
0x0100, 0xFEFF, 0xFEFF, 0x0200,
0xFBFF, 0xFBFF, 0x0300, 0x0200,
0xFEFF, 0x0000, 0xFFFF, 0xFDFF,
0x0000, 0x0000, 0xFFFF, 0x0100,
0xFFFF, 0x0000, 0x0000, 0xFFFF,
0x0200, 0x0100, 0xFEFF, 0x0100,
0xFDFF, 0xFCFF, 0x0400, 0x0300,
0xFFFF, 0xFEFF, 0x0100, 0x0200,
0xFEFF, 0xFFFF, 0x0200, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0xFFFF, 0x0000, 0x0100,
0xFFFF, 0x0000, 0x0100, 0x0000,
0xFFFF, 0x0100, 0x0000, 0x0000,
0x0000, 0xFFFF, 0x0000, 0x0100,
0x0000, 0xFFFF, 0x0000, 0x0200,
0xFDFF, 0xFEFF, 0x0300, 0x0100,
0x0000, 0x0200, 0xFFFF, 0xFEFF,
0x0100, 0x0000, 0x0000, 0xFFFF,
0x0200, 0x0400, 0xFDFF, 0xFDFF,
0x0200, 0x0100, 0xFEFF, 0x0000,
0x0100, 0x0100, 0xFFFF, 0xFFFF,
0x0000, 0x0000, 0x0100, 0xFFFF,
0x0100, 0x0000, 0xFFFF, 0x0100,
0xFFFF, 0x0000, 0x0000, 0x0100,
0xFEFF, 0xFDFF, 0x0300, 0x0300,
0xFDFF, 0xFDFF, 0x0300, 0x0300,
0xFEFF, 0x0000, 0x0100, 0xFFFF,
0x0100, 0x0000, 0x0000, 0x0000,
0x0000, 0x0100, 0xFFFF, 0x0000,
0xFFFF, 0xFDFF, 0x0200, 0x0300,
0xFDFF, 0xFEFF, 0x0300, 0x0100,
0xFFFF, 0xFDFF, 0x0200, 0x0300,
0xFEFF, 0x0000, 0x0100, 0x0000,
0xFEFF, 0xFEFF, 0x0300, 0x0100,
0x0100, 0x0300, 0xFDFF, 0xFEFF,
0x0000, 0xFCFF, 0x0300, 0x0300,
0xFEFF, 0x0100, 0x0000, 0x0000,
0xFEFF, 0xFDFF, 0x0300, 0x0200,
0x0000, 0x0300, 0xFEFF, 0xFDFF,
0x0200, 0x0100, 0xFFFF, 0xFFFF,
0x0100, 0x0200, 0xFEFF, 0xFFFF,
0x0100, 0x0000, 0xFFFF, 0x0000,
0x0000, 0xFEFF, 0x0100, 0x0300,
0xFCFF, 0xFBFF, 0x0500, 0x0400,
0xFDFF, 0xFFFF, 0x0200, 0x0000,
0x0100, 0x0200, 0xFEFF, 0xFEFF,
0x0200, 0x0300, 0xFEFF, 0xFCFF,
0x0400, 0x0400, 0xFCFF, 0xFDFF,
0x0200, 0x0200, 0xFEFF, 0xFEFF,
0x0200, 0x0100, 0xFEFF, 0x0000
};

const uint32_t samples_in_sample_buffer = ARRAY_SIZE(sample_buffer);
#endif /* ENABLE_TICK_SAMPLE */