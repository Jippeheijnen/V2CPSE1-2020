 /*#############################################################
 #                 (c) Jippe Heijnen 2019                     #
 #                                                            #
 #   Distributed under the Boost Software License v1.0.       #
 #   (See accompanying file LICENSE_1_0.txt or copy at        #
 #          https://www.boost.org/LICENSE_1_0.txt)            #
 #############################################################*/

  .cpu cortex-m0
  .text
  .align 1
  .global application, print_asciz

//  In dit programma wordt een string opgeslagen,
//  die vervolgens doorgegeven wordt aan uart_put_char

// Dit is de hello world string die opgeslagen moet worden.
str:
  .asciz "Hello world, the ANSWER is 42! @[]`{}~\n"

// Dit geeft het adres van de string door aan print_asciz functie
application:
  push { lr }                                // Link register opslaan
  ldr r0, =str                               // zet het adres van de string in R0
  bl print_asciz
  pop { pc }



toggle:
  push { lr }
  cmp r0, #'A'
  bge greaterEqualA
  b klaar

greaterEqualA:
  cmp r0, #'Z'
  bge lesserEqualZ
    add r0, r0, #32
  b klaar

lesserEqualZ:
  cmp r0, #'a'
  bge greaterEquala
  b klaar

greaterEquala:
  cmp r0, #'z'
  ble lesserEqualz
  b klaar

lesserEqualz:
  sub r0, r0, #32

klaar:
  pop { pc }


// Deze functie loopt over een string en geeft deze per char door aan uart_put_char
print_asciz:
  push { r5, lr }                           // Stel R5 en Link register veilig
  mov r5, r0                                // Zet het adres vd. string in R5

// Deze loop gaat over de adressen zodat elk character doorgegeven kan worden.
loop:
  ldrb r0, [ r5 ]                            // De inhoud van het adres in R5 wordt in r0 gezet
  add r0, r0, #0                            // Voeg daar 1 aan toe om mogelijk de Zero flag te raisen.
  beq done                                  // Als de Zero flag op 1 staat ga dan naar done
  bl toggle
  bl uart_put_char
  add r5, r5, #1                            // je voegt #1 toe aan R5 zodat het volgende adres gelezen gaat worden
  b loop                                    // begin de loop opnieuw

// als de nulbyte bereikt is.
done:
  pop { r5, pc }