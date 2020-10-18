.cpu cortex-m0
.text
.align 2
.global decompressor
/*
De decompressor subroutine in assembler geschreven
*/

decompressor:
    push { r3, r5, r6, r7, lr }
    ldr r5, =msg // in r5 zit nu de tekst
    mov r3, r0 // r3 heeft nu de buffer array

mainLoop:
    ldrb r4, [ r5 ] // eerste char toevoegen
    add r4, r4, #0 // checken voor \0
    beq done
    cmp r4, #'@' // checken voor een marker
    beq createMatch
    mov r0, r4
    bl uart_put_char
    bl startBuffer
    add r5, r5, #1
    b mainLoop

createMatch:
    add r5, r5, #1
    ldrb r4, [ r5 ]
    mov r6, r4 // de offset inladen
    sub r6, r6, #'0' // naar numeriek vertalen
    add r5, r5, #1
    ldrb r4, [ r5 ]
    mov r7, r4 // de lengte inladen
    sub r7, r7, #'0'

matchLoop:
    cmp r7, #0
    beq endMatch
    ldrb r4, [ r3, r6 ] // offset inladen in de buffer array
    mov r0, r4
    bl uart_put_char
    bl startBuffer
    sub r7, r7, #1
    b matchLoop

endMatch:
    add r5, r5, #1
    b mainLoop

startBuffer:
    push {r3, r4, lr }
    mov r1, #39

bufferLoop:
    cmp r1, #0
    beq endBuffer
    sub r2, r1, #1
    ldrb r0, [ r3, r2 ]
    strb r0, [ r3, r1 ]
    sub r1, r1, #1
    b bufferLoop

endBuffer:
    strb r4, [r3, #0 ]
    pop { r3, r4, pc }

done:
    pop { r5, r6, r7, pc }


