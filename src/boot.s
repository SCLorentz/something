.section .text
.global _start

/* entry point */
_start:
    /* inicializa stack pointer */
    la sp, stack_top

    /* chama kernel_main */
    call kernel_main

1:  /* loop infinito */
    j 1b

/* stack */
.section .bss
.align 16
stack_bottom:
    .skip 16*1024  /* 16 KiB de stack */
stack_top:
