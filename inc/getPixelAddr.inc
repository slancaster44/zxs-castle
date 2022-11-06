
;;hl :: x,y coords

getPixelAddr:
    push af
    push bc

    ;;Ld and mask out x coord
    ld a,h
    rr a
    rr a
    rr a
    and 0b00011111
    ld b,a

    ;;Mask in y bits 3,4,5
    ld a,l
    and 0b00111000
    rl a
    rl a

    or b ;;a now has the proper low byte
    ld b,l
    ld l,a ;;Save low byte


    ld a,b ;;Gather y coord
    and 0b00000111
    ld h,a

    ld a,b
    and 0b11000000
    rra
    rra
    rra
    add a,0b01000000
    or h
    ld h,a

    pop bc
    pop af
    ret