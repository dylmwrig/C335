    .text
    .syntax unified
    .thumb
    .global inc 
    .type   inc, %function
inc:
    adds    r0,r0,#1
    bx  lr
