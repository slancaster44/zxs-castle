
mkScreenBlack:

    ld a,PAPER_BLACK
    call CHANGE_BORDER

    ld hl,COLOR_ATTR_START
    ld de,COLOR_ATTR_END+1
    or INK_WHITE

    ld b,a
.loop:
    ld (hl),b
    inc hl

    ld a,d
    cp h
    jp nz, .loop

    ld a,e
    cp l
    jp nz, .loop

    ret