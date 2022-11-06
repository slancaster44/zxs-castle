
;;Arguments in
;;de: start of tile info
;;ix: start addr of coords
;;bc: address after end of coords
batchPaint:
    push hl
    dec bc ;; And end lable will be off by one address

.loop
    ;;Get current coordinate & print
    ld h,(ix+1)
    ld l,(ix)
    call print8x8

    ;;Get next addr
    inc ix
    inc ix

    ld hl,ix
    sbc hl,bc
    jp m, .loop

    pop hl
    ret

;;Arguments in
;;a desired attribute byte
;;ix: start addr of coords
;;bc: address after end of coords
batchAttr:
    push hl
    dec bc

.loop
    ld h,(ix+1)
    ld l,(ix)
    call applyAttrAt

    inc ix
    inc ix

    ld hl,ix
    sbc hl,bc

    jp m, .loop

.end:
    pop hl
    ret

