
;; hl:: X,Y Off top left corner in screen ram
;; de:: start of tile information
print8x8:
    push af
    push bc
    push de
    push hl
    push ix

    
    ld b,8

.loop:
    ld ix,hl
    call getPixelAddr

    ld a,(de)
    ld (hl),a
    inc de

    ld hl,ix
    inc l
    djnz .loop

.cont:
    pop ix
    pop hl
    pop de
    pop bc
    pop af
    ret

;a:  the attribute to be applied
;hl: the coord of the attribute
applyAttrAt:
    push bc
    push de
    push af
    push hl

    ld c,a ;;Save attribute

    ;;Divide by 8 to find attr coords
    ld a,h
    srl a
    srl a
    srl a
    ld h,a

    ld a,l
    srl a
    srl a
    srl a
    ld l,a

;;hl now contains the coords of 
;;the location in screen attr mem
;;we now need to convert that to
;;a linear location

    ld b,h
    ld h,l
    ld l,b

    ld b,h
    ld h,00
    ld de,32
.mul_loop:
    add hl,de
    djnz .mul_loop

;;Apply attribute and clean up
    ld de,COLOR_ATTR_START
    add hl,de
    ld (hl),c

    ld a,c
    pop hl
    pop af
    pop de
    pop bc
    ret