
CastleHP:
    db 64h

Player:
.curSpriteID
    db 00h
.curHealth
    db 10h
.curPos
    dw 8080h
.lastPos
    dw 9090h

playerHandler:
    call MovePlayer
    call DrawPlayer
    call RepaintOldPlayerPosition
.exit
    ret

MovePlayer:
    push bc
    push af
    push hl

    ld hl,(Player.curPos)

.readInKeys:
    ld bc,READ_ASDFG
    in a,(c)
    
    bit KEY_BIT_A,a
    jr z, .moveLeft

    bit KEY_BIT_S,a
    jr z, .moveDown

    bit KEY_BIT_D,a
    jr z,.moveRight

    ld bc,READ_QWERT
    in a,(c)
    bit KEY_BIT_W,a
    jr z,.moveUp

    jr .exit

.moveUp:
    ld bc,hl ;;Save old coords in bc, so they can be saved in memory later
    ld a,l
    sub 08h
    ld l,a
    jr .checkBounds
.moveDown:
    ld bc,hl
    ld a,l
    add a,08h
    ld l,a
    jr .checkBounds
.moveLeft:
    ld bc,hl
    ld a,h
    sub 08h
    ld h,a
    jr .checkBounds
.moveRight:
    ld bc,hl
    ld a,h
    add a,08h
    ld h,a
    jr .checkBounds

.checkBounds:
    ld a,h
    cp 31h ;TODO: Eliminate magic value
    jp p,.saveAndExit

    ld a,l
    cp 39h
    jp p,.saveAndExit

    jr .exit

.saveAndExit:
    ld (Player.lastPos),bc
    ld (Player.curPos),hl

.exit
    pop hl
    pop af
    pop bc
    ret

DrawPlayer:
    push hl
    push de
    push af

    ld hl,(Player.curPos)
    ld de,cobbleTile
    call print8x8

    ld hl,(Player.curPos)
    ld a,PAPER_WHITE
    or INK_PINK
    call applyAttrAt

.exit:
    pop af
    pop de
    pop hl
    ret

RepaintOldPlayerPosition:  
    push de
    push ix
    push bc
    push hl
    push af

    ld ix,roadCoords
    ld hl,roadCoords.end
    ld de,roadCoords
    sbc hl,de
    ld bc,hl
    ld hl,(Player.lastPos)
    call cpdr16
    jr z,.paintRoadOnOldPlayerLoc

    ld ix,castleDoorCoords
    ld hl,castleDoorCoords.end
    ld de,castleDoorCoords
    sbc hl,de
    ld bc,hl
    ld hl,(Player.lastPos)
    call cpdr16
    jr z,.paintDoorOnOldPlayerLoc

    ld ix,grassCoords
    ld hl,grassCoords.end
    ld de,grassCoords
    sbc hl,de
    ld bc,hl
    ld hl,(Player.lastPos)
    call cpdr16
    jr z,.paintGrassOnOldPlayerLoc

.paintBlackOnOldPlayerLoc:
    ld hl,(Player.lastPos)
    ld de,emptyTile
    call print8x8
    
    ld hl,(Player.lastPos)
    ld a,PAPER_BLACK
    or INK_WHITE
    call applyAttrAt

    jr .exit

.paintRoadOnOldPlayerLoc:
    ld hl,(Player.lastPos)
    ld de,cobbleTile
    call print8x8
    
    
    ld hl,(Player.lastPos)
    ld a,PAPER_WHITE
    or INK_BLACK
    call applyAttrAt

    jr .exit

.paintGrassOnOldPlayerLoc:
    ld hl,(Player.lastPos)
    ld de, grassTile
    call print8x8

    ld hl,(Player.lastPos)
    ld a,PAPER_BLACK
    or INK_GREEN
    call applyAttrAt

    jr .exit

.paintDoorOnOldPlayerLoc:
    ld hl,(Player.lastPos)
    ld de,barTile
    call print8x8

    ld hl,(Player.lastPos)
    ld a,PAPER_RED
    or INK_YELLOW
    call applyAttrAt

    jr .exit
.exit
    pop af
    pop hl
    pop bc
    pop ix
    pop de
    ret