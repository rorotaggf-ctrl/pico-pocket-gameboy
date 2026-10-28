#include "hw_bridge.h"

    .section .bss
    .align 4
dy:     .space 4
dvy:    .space 4
cx:     .space 4
dsc:    .space 4

    .section .text
    .align 4
    .global din_init
    .type din_init, @function

din_init:
    entry   a1, 32

    movi    a2, 190
    movi    a3, dy
    s32i    a2, a3, 0

    movi    a2, 0
    movi    a3, dvy
    s32i    a2, a3, 0

    movi    a2, 240
    movi    a3, cx
    s32i    a2, a3, 0

    movi    a2, 0
    movi    a3, dsc
    s32i    a2, a3, 0

    movi    a6, c_black
    call8   hw_screen

    movi    a6, 0
    movi    a7, 206
    movi    a8, 240
    movi    a9, 2
    movi    a10, c_white
    call8   hw_frect

    retw.n

    .align 4
    .global din_run
    .type din_run, @function

din_run:
    entry   a1, 32

    // b_b (Bit 5) prüfen
    bbci    a2, 5, .Ljump
    movi    a2, 1
    retw.n

.Ljump:
    // Dino löschen
    movi    a3, dy
    l32i    a4, a3, 0
    movi    a6, 20
    mov     a7, a4
    movi    a8, 16
    movi    a9, 16
    movi    a10, c_black
    call8   hw_frect

    // b_a (Bit 4) prüfen & Sprung
    movi    a3, dy
    l32i    a4, a3, 0
    movi    a5, 190
    bne     a4, a5, .Lgrav
    bbci    a2, 4, .Lgrav
    movi    a6, -10
    movi    a7, dvy
    s32i    a6, a7, 0

.Lgrav:
    movi    a6, dvy
    l32i    a7, a6, 0
    addi    a7, a7, 1
    s32i    a7, a6, 0

    movi    a3, dy
    l32i    a4, a3, 0
    add     a4, a4, a7
    movi    a5, 190
    blt     a4, a5, .Lsty
    mov     a4, a5
    movi    a7, 0
    movi    a6, dvy
    s32i    a7, a6, 0

.Lsty:
    s32i    a4, a3, 0

    // Kaktus löschen
    movi    a8, cx
    l32i    a9, a8, 0
    mov     a6, a9
    movi    a7, 192
    movi    a8, 10
    movi    a9, 14
    movi    a10, c_black
    call8   hw_frect

    // Kaktus bewegen
    movi    a8, cx
    l32i    a9, a8, 0
    addi    a9, a9, -4
    bgei    a9, 0, .Lstc
    movi    a9, 235
    movi    a10, dsc
    l32i    a11, a10, 0
    addi    a11, a11, 1
    s32i    a11, a10, 0

.Lstc:
    s32i    a9, a8, 0

    // Kollision
    movi    a8, cx
    l32i    a9, a8, 0
    movi    a10, 36
    bgt     a9, a10, .Ldraw
    movi    a10, 12
    blt     a9, a10, .Ldraw
    movi    a3, dy
    l32i    a4, a3, 0
    movi    a5, 178
    blt     a4, a5, .Ldraw

    movi    a2, 1
    retw.n

.Ldraw:
    movi    a3, dy
    l32i    a7, a3, 0
    movi    a6, 20
    movi    a8, 16
    movi    a9, 16
    movi    a10, c_green
    call8   hw_frect

    movi    a8, cx
    l32i    a6, a8, 0
    movi    a7, 192
    movi    a8, 10
    movi    a9, 14
    movi    a10, c_red
    call8   hw_frect

    movi    a2, 0
    retw.n