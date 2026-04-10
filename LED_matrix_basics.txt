# Light:
#   LED[0][0] = Red
#   LED[1][0] = Green
#   LED[2][0] = Blue
#   LED[3][0] = White

# This is a RISC-V 32-bit processor (word = 4 bytes)
# This shows how to decide which LED to light and in which colour

.equ BASE, 0xf0000000

.text
main:
    li   t0, 0xf0000000

    li   t1, 0x00FF0000     # Red
    sw   t1, 0(t0)          # col=0, row=0  → offset = (0*7+0)*4 = 0

    li   t1, 0x0000FF00     # Green
    sw   t1, 4(t0)          # col=1, row=0  → offset = (0*7+1)*4 = 4

    li   t1, 0x000000FF     # Blue
    sw   t1, 8(t0)          # col=2, row=0  → offset = 8

    li   t1, 0x00FFFFFF     # White
    sw   t1, 12(t0)         # col=3, row=0  → offset = 12
    
    li   t1, 0x00FABDFF
    sw   t1, 68(t0)

loop:
    j loop





#####################################
#####################################

.text
main:
    li   a0, 0              # row = 0
    li   a1, 0              # col = 0
    li   a2, 0x00FF0000     # Red
    call set_led

    li   a0, 1              # row = 0
    li   a1, 0              # col = 1
    li   a2, 0x0000FF00     # Green
    call set_led

    li   a0, 2              # row = 0
    li   a1, 0              # col = 2
    li   a2, 0x000000FF     # Blue
    call set_led

loop:
    j loop

# --- Subroutine ---
set_led:
    li   t0, 7
    mul  t1, a0, t0
    add  t1, t1, a1
    slli t1, t1, 2
    li   t0, 0xF0000000
    add  t0, t0, t1
    sw   a2, 0(t0)
    ret





#********************************************************************************
# Counter(Binary) : Count from 0 to (2 to the power of specified column value)
#********************************************************************************


# Binary Timer — counts 0 to 127, displayed in binary on Row 0
# col 6 = bit 0 (LSB), col 0 = bit 6 (MSB)
# RV32IM required (uses mul)

.equ BASE,       0xF0000000
.equ ON_COLOR,   0x0000FF00     # Green for ON
.equ OFF_COLOR,  0x00000000     # Off
.equ DELAY_VAL,  1        # Tune this to adjust speed

.text
main:
    li   s0, 0              # s0 = counter (0 to 127)

timer_loop:
    li   t0, 128
    bge  s0, t0, reset      # if counter >= 128, reset to 0

    mv   a0, s0             # pass current count to display
    call display_binary

    # Delay (~1 second)
    li   t0, DELAY_VAL
delay:
    addi t0, t0, -1
    bne  t0, zero, delay

    addi s0, s0, 1          # counter++
    j    timer_loop

reset:
    li   s0, 0
    j    timer_loop


# display_binary(a0 = number to display)
# Checks each bit of a0, lights col accordingly on row 0
# col 6 = bit 0, col 5 = bit 1, ... col 0 = bit 6

display_binary:
    li   s1, 6              # bit position (0 to 6), also col = 6 - bit

bit_loop:
    blt  s1, zero, display_done

    # Extract bit: t1 = (a0 >> bit_pos) & 1
    srl  t1, a0, s1         # shift right by s1
    andi t1, t1, 1          # isolate LSB

    # col = 6 - s1
    li   t2, 3
    sub  t2, t2, s1         # t2 = col index

    # Compute address: BASE + (0 * 7 + col) * 4
    slli t3, t2, 2          # offset = col * 4 (row=0, so row*7=0)
    li   t4, BASE
    add  t4, t4, t3         # address

    # Choose color
    beq  t1, zero, write_off
write_on:
    li   t5, ON_COLOR
    j    do_write
write_off:
    li   t5, OFF_COLOR
do_write:
    sw   t5, 0(t4)

    addi s1, s1, -1         # next bit
    j    bit_loop

display_done:
    ret




