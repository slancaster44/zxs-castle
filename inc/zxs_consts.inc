;; Character color encoding ;;;;;;;;;;;
; Usage: Or the desired attributes together
; to produce the correct encoding for a given
; pallette
;
; Example:
;   ld a, 0
;   or a, BRIGHT
;   or a, PAPER_BLUE
;   or a, INK_RED
;
; The above creates and encoding for
; a bright character with blue background
; and red foreground
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
FLASH   equ 10000000b
BRIGHT  equ 01000000b

PAPER_BLACK     equ 00000000b
PAPER_BLUE      equ 00001000b
PAPER_RED       equ 00010000b
PAPER_PINK      equ 00011000b
PAPER_GREEN     equ 00100000b
PAPER_CYAN      equ 00101000b
PAPER_YELLOW    equ 00110000b
PAPER_WHITE     equ 00111000b

INK_BLACK   equ 00000000b
INK_BLUE    equ 00000001b
INK_RED     equ 00000010b
INK_PINK    equ 00000011b
INK_GREEN   equ 00000100b
INK_CYAN    equ 00000101b
INK_YELLOW  equ 00000110b
INK_WHITE   equ 00000111b

;; Memory Map
ROM_START   equ 0000h
ROM_SIZE    equ 4000h
ROM_END     equ 3FFFh

;;A bitmap that indicates which pixels
;;show the paper color, and which show
;;the ink color
SCREEN_BITMAP_START equ 4000h
SCREEN_BITMAP_SIZE  equ 1800h
SCREEN_BITMAP_END   equ 57FFh

;;A tile map showing which 8x8
;;squares have which colors
COLOR_ATTR_START    equ 5800h
COLOR_ATTR_SIZE     equ 0300h
COLOR_ATTR_END      equ 5AFFh

BASIC_START equ 5B00h 
BASIC_SIZE  equ 01CBh
BASIC_END   equ 5CCAh

CONTENDED_USER_RAM_START    equ 5CCBh
CONTENDED_USER_RAM_SIZE     equ 2335h
CONTENDED_USER_RAM_END      equ 7FFFh

USER_RAM_START equ 8000h
USER_RAM_SIZE  equ 7F58h
USER_RAM_END   equ 0xFF57

USER_DEF_GRAPHICS_START equ 0xFF58
USER_DEF_GRAPHICS_SIZE  equ 0xA7
USER_DEF_GRAPHICS_END   equ 0xFFFF

;; I/O Map ;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Usage: Reading from these ports will
;return a byte where a zero in the one
;of the lowest 5 bits indicates that the
;corresponding key is depressed
;
;ld bc,<key_set_to_read>
;in a, (c)
;bit <key_bit>,a ; Sets zero flag to 0 if it the given key was depressed
;
READ_SHIFT_ZXCV         equ 0xFEFE
KEY_BIT_SHIFT           equ 0
KEY_BIT_Z               equ 1
KEY_BIT_X               equ 2
KEY_BIT_C               equ 3
KEY_BIT_V               equ 4

READ_ASDFG              equ 0xFDFE
KEY_BIT_A               equ 0
KEY_BIT_S               equ 1
KEY_BIT_D               equ 2
KEY_BIT_F               equ 3
KEY_BIT_G               equ 4

READ_QWERT              equ 0xFBFE
KEY_BIT_Q               equ 0
KEY_BIT_W               equ 1
KEY_BIT_E               equ 2
KEY_BIT_R               equ 3
KEY_BIT_T               equ 4

READ_12345              equ 0xF7FE
KEY_BIT_1               equ 0
KEY_BIT_2               equ 1
KEY_BIT_3               equ 2
KEY_BIT_4               equ 3
KEY_BIT_5               equ 4

READ_09876              equ 0xEFFE
KEY_BIT_0               equ 0
KEY_BIT_9               equ 1
KEY_BIT_8               equ 2
KEY_BIT_7               equ 3
KEY_BIT_6               equ 4

READ_POIUY              equ 0xDFFE
KEY_BIT_P               equ 0
KEY_BIT_O               equ 1
KEY_BIT_I               equ 2
KEY_BIT_U               equ 3
KEY_BIT_Y               equ 4

READ_ENTER_LKJH         equ 0xBFFE
KEY_BIT_ENTE            equ 0
KEY_BIT_L               equ 1
KEY_BIT_K               equ 2
KEY_BIT_J               equ 3
KEY_BIT_H               equ 4

READ_SPACE_SYM_SHFT_MNB equ 0x7FFE
KEY_BIT_SPACE           equ 0
KEY_BIT_SYM             equ 1
KEY_BIT_M               equ 2
KEY_BIT_N               equ 3
KEY_BIT_B               equ 4


;; Character Set ;;;;;;;;;;;;;;
; The hex encodings for the zx spectrum character set

NEWLINE equ 0Dh


;; Useful ROM Routines Provided by the Spectrum
; Usage: call <routine_name> or rst <routine_name>
; will jump to the space in rom that the routine exists, and
; execute the routine.
;
; Sometimes, arguments may be passed to a
; rom routine using the registers

;; Command: call
;; Arguments: None
;; Description: Clears the screen
CLR_SCREEN equ 0DAFh

;;Command: call
;;Arguments: a
;;Changes border color to color in a
CHANGE_BORDER equ 229Bh

;; Command: rst
;;Arguments: a register
;;Description: Prints character encoded in a
PRINT_CHAR equ $10

;;Multiplies hl by the immediate
;;    1011 :x
;;    1101 :y
;;    ----
;;    1011
;;   00000
;;  101100
mulhl macro imm?
    push af
    push bc
    push de

    ld c,imm? ;;Values loaded, now hl * c
    ld b,16

    ld de,hl    ;;de stores x-value
    ld hl,0000h ;;hl stores result

.loop:
    bit 0,e
    jr z,.continue
    
    ld a,b
    ld b,0
    add hl,bc
    ld b,a
.continue:
    sla c
    srl de
    djnz .loop

.exit:
    pop af
    pop de
    pop bc
endm
    
;;ix contains starting address
;;bc contains index
;;hl contains comparision word
;;WARNING: Clobbers 'a' register
cpdr16:
    push de

.loop:
    ld e,(ix)
    ld d,(ix+1)

    sbc hl,de
    jp z,.exit
    add hl,de

.continue:
    inc ix
    inc ix
    dec bc
    dec bc

    xor a
    or b
    or c
    cp 0
    jr nz, .loop
    add a, 1 ;;Clear zero flag

.exit:
    pop de
    ret


