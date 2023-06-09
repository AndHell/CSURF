/* DO NOT EDIT! generated by ./autogen */

.intel_syntax noprefix

#include "uintbig_namespace.h"
#include "fp_namespace.h"

.section .rodata

.set pbits,511
.set pbytes,64
.set plimbs,8
.inv_min_p_mod_r: /* -p^-1 mod 2^64 */
    .quad 0x60475c3f209ea969

.global fp_0
fp_0:
    .zero 64

.global fp_1
fp_1: /* 2^512 mod p */
    .quad 0x48b9985c47a5648b, 0xc7d7cccea3e3b2a6, 0x220f019086e0aac2, 0xe346002125f57b5c
    .quad 0x1f63d63d59bee93f, 0x3d0075d581c5df9c, 0xf9e45bd8e073bb3f, 0x3d82af6c2e7d53dc

.global fp_2
fp_2: /* 2^513 mod p */
    .quad 0x545bb8d751d73fef, 0x27a233377e68a0d9, 0x4f7858fbe5618e71, 0x67a355a2ade7752c
    .quad 0xf3e8f3e47c12caea, 0xe3abbd9cd9785f16, 0xf1bf80fa0bb8b4e8, 0x3a30eea717246e58

.r_squared_mod_p: /* (2^512)^2 mod p */
    .quad 0xb03280a70a3f4a61, 0xea2247646954b888, 0xbf434f44b9480893, 0xad7a83acbee5d362
    .quad 0x3061c9a3fcf4ccb4, 0xe811ef3c1280a3bd, 0xc46e495c9ef4963d, 0x086386d9f5bbf535

.p_minus_1_halves:
    .quad 0x9e8bbbf09eb9c493, 0x3406b332e4af6239, 0xfa52d512942fe38a, 0xaf74554fcf01c0c5
    .quad 0xa56f5c4b1bb583ca, 0xcb2a97071509b010, 0x81049b5bda9760ca, 0x206a3818a2eb1cb0

.section .data
.global fp_mulsq_count
fp_mulsq_count:
    .quad 0
.global fp_sq_count
fp_sq_count:
    .quad 0
.global fp_addsub_count
fp_addsub_count:
    .quad 0

.section .text
.p2align 4,,15

.global fp_copy
fp_copy:
    cld
    mov rcx, plimbs
    rep movsq
    ret

.global fp_cmov
fp_cmov:
    movzx rax, dl
    neg rax
    .set k, 0
    .rept plimbs
        mov rcx, [rdi + 8*k]
        mov rdx, [rsi + 8*k]

        xor rdx, rcx
        and rdx, rax
        xor rcx, rdx

        mov [rdi + 8*k], rcx

        .set k, k+1
    .endr
    ret

.global fp_cswap
fp_cswap:
    movzx rax, dl
    neg rax
    .set k, 0
    .rept plimbs
        mov rcx, [rdi + 8*k]
        mov rdx, [rsi + 8*k]

        mov r8, rcx
        xor r8, rdx
        and r8, rax

        xor rcx, r8
        xor rdx, r8

        mov [rdi + 8*k], rcx
        mov [rsi + 8*k], rdx

        .set k, k+1
    .endr
    ret

.reduce_once:
    push rbp
    mov rbp, rdi

    mov rdi, [rbp + 0]
    sub rdi, [rip + uintbig_p + 0]
    mov rsi, [rbp + 8]
    sbb rsi, [rip + uintbig_p + 8]
    mov rdx, [rbp + 16]
    sbb rdx, [rip + uintbig_p + 16]
    mov rcx, [rbp + 24]
    sbb rcx, [rip + uintbig_p + 24]
    mov r8,  [rbp + 32]
    sbb r8,  [rip + uintbig_p + 32]
    mov r9,  [rbp + 40]
    sbb r9,  [rip + uintbig_p + 40]
    mov r10, [rbp + 48]
    sbb r10, [rip + uintbig_p + 48]
    mov r11, [rbp + 56]
    sbb r11, [rip + uintbig_p + 56]

    setnc al
    movzx rax, al
    neg rax

.macro cswap2, r, m
    xor \r, \m
    and \r, rax
    xor \m, \r
.endm

    cswap2 rdi, [rbp + 0]
    cswap2 rsi, [rbp + 8]
    cswap2 rdx, [rbp + 16]
    cswap2 rcx, [rbp + 24]
    cswap2 r8, [rbp + 32]
    cswap2 r9, [rbp + 40]
    cswap2 r10, [rbp + 48]
    cswap2 r11, [rbp + 56]

    pop rbp
    ret

.global fp_add2
fp_add2:
    mov rdx, rdi
.global fp_add3
fp_add3:
    addq [fp_addsub_count+rip],1
    push rdi
    call uintbig_add3
    pop rdi
    jmp .reduce_once

.global fp_sub2
fp_sub2:
  mov rdx, rdi
  xchg rsi, rdx
.global fp_sub3
fp_sub3:
    addq [fp_addsub_count+rip],1
    push rdi
    call uintbig_sub3
    pop rdi
    neg rax

    sub rsp, pbytes

    mov rcx, [rip + uintbig_p +  0]
    and rcx, rax
    mov [rsp + 0],rcx
    .set k, 1
    .rept plimbs-1
        mov rcx, [rip + uintbig_p + 8*k]
        and rcx, rax
        mov [rsp + 8*k], rcx
        .set k, k+1
    .endr

    mov rcx, [rsp +  0]
    add rcx, [rdi +  0]
    mov [rdi +  0], rcx
    .set k, 1
    .rept plimbs-1
        mov rcx, [rsp + 8*k]
        adc rcx, [rdi + 8*k]
        mov [rdi + 8*k], rcx
        .set k, k+1
    .endr

    add rsp, pbytes
    ret


/* Montgomery arithmetic */

.global fp_mul2
fp_mul2:
  mov rdx, rdi
.global fp_mul3
fp_mul3:
    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15

    push rdi

    addq [fp_mulsq_count+rip],1

    mov rdi, rsi
    mov rsi, rdx

    xor r8,  r8
    xor r9,  r9
    xor r10, r10
    xor r11, r11
    xor r12, r12
    xor r13, r13
    xor r14, r14
    xor r15, r15
    xor rbp, rbp

    /* flags are already cleared */

.macro MULSTEP, k, r0, r1, r2, r3, r4, r5, r6, r7, r8

    mov rdx, [rsi +  0]
    mulx rcx, rdx, [rdi + 8*\k]
    add rdx, \r0
    mulx rcx, rdx, [rip + .inv_min_p_mod_r]

    xor rax, rax /* clear flags */

    mulx rbx, rax, [rip + uintbig_p +  0]
    adox \r0, rax

    mulx rcx, rax, [rip + uintbig_p +  8]
    adcx \r1, rbx
    adox \r1, rax

    mulx rbx, rax, [rip + uintbig_p + 16]
    adcx \r2, rcx
    adox \r2, rax

    mulx rcx, rax, [rip + uintbig_p + 24]
    adcx \r3, rbx
    adox \r3, rax

    mulx rbx, rax, [rip + uintbig_p + 32]
    adcx \r4, rcx
    adox \r4, rax

    mulx rcx, rax, [rip + uintbig_p + 40]
    adcx \r5, rbx
    adox \r5, rax

    mulx rbx, rax, [rip + uintbig_p + 48]
    adcx \r6, rcx
    adox \r6, rax

    mulx rcx, rax, [rip + uintbig_p + 56]
    adcx \r7, rbx
    adox \r7, rax

    mov rax, 0
    adcx \r8, rcx
    adox \r8, rax


    mov rdx, [rdi + 8*\k]

    xor rax, rax /* clear flags */

    mulx rbx, rax, [rsi +  0]
    adox \r0, rax

    mulx rcx, rax, [rsi +  8]
    adcx \r1, rbx
    adox \r1, rax

    mulx rbx, rax, [rsi + 16]
    adcx \r2, rcx
    adox \r2, rax

    mulx rcx, rax, [rsi + 24]
    adcx \r3, rbx
    adox \r3, rax

    mulx rbx, rax, [rsi + 32]
    adcx \r4, rcx
    adox \r4, rax

    mulx rcx, rax, [rsi + 40]
    adcx \r5, rbx
    adox \r5, rax

    mulx rbx, rax, [rsi + 48]
    adcx \r6, rcx
    adox \r6, rax

    mulx rcx, rax, [rsi + 56]
    adcx \r7, rbx
    adox \r7, rax

    mov rax, 0
    adcx \r8, rcx
    adox \r8, rax

.endm

    MULSTEP 0, r8,  r9,  r10, r11, r12, r13, r14, r15, rbp
    MULSTEP 1, r9,  r10, r11, r12, r13, r14, r15, rbp, r8
    MULSTEP 2, r10, r11, r12, r13, r14, r15, rbp, r8,  r9
    MULSTEP 3, r11, r12, r13, r14, r15, rbp, r8,  r9,  r10
    MULSTEP 4, r12, r13, r14, r15, rbp, r8,  r9,  r10, r11
    MULSTEP 5, r13, r14, r15, rbp, r8,  r9,  r10, r11, r12
    MULSTEP 6, r14, r15, rbp, r8,  r9,  r10, r11, r12, r13
    MULSTEP 7, r15, rbp, r8,  r9,  r10, r11, r12, r13, r14

    pop rdi

    mov [rdi +  0], rbp
    mov [rdi +  8], r8
    mov [rdi + 16], r9
    mov [rdi + 24], r10
    mov [rdi + 32], r11
    mov [rdi + 40], r12
    mov [rdi + 48], r13
    mov [rdi + 56], r14

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    jmp .reduce_once

.global fp_sq1
fp_sq1:
    mov rsi, rdi
.global fp_sq2
fp_sq2:
    /* TODO implement optimized Montgomery squaring */
    mov rdx, rsi
    addq [fp_sq_count+rip],1
    jmp fp_mul3

