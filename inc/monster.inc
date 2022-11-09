;;Add any new monsters
;;Remove any dead monsters
;;Update monster positions
;;Redraw monsters
monsterHandler:
.clearTheDead:
    call ClearDeadMonsters

.drawMonsters:
    call DrawMonsterHeap

.moveMonsters:
    call UpdateMonsterPositions

.exit:
    ret



;;Monster Heap Entry Format
;; Byte 0: Monster Sprite
;; Byte 1: Health Point of Monster
;; Byte 2: The path the monster is taking
;; Byte 3: Index in path the monster is on

;; Arguments:
;; c: Sprite
;; d: Health Points
;; e: path
AllocMonster:
    push bc
    push ix

    ld ix,MonsterHeap.startOfHeap

    ld a,(MonsterHeap.numActiveMonsters)
    cp 0
    jr z, .insertDataToHeap

    ld b,a
.addrCalcLoop
    inc ix
    inc ix
    inc ix
    inc ix

    djnz .addrCalcLoop

.insertDataToHeap
    ld (ix),c
    ld (ix+1),d
    ld (ix+2),e
    ld (ix+3),0 ;Start monster on start of path

    ld de,ix
    ld ix,MonsterHeap.locOfLastMonster
    ld (ix),de

    ld ix,MonsterHeap.numActiveMonsters
    inc (ix)

.exit
    pop ix
    pop bc
    ret

ClearDeadMonsters:
    push ix
    push bc
    push af
    push iy
    push de
    push hl

    ld a,(MonsterHeap.numActiveMonsters)
    cp 0
    jp z, .exit

    ld b,a
    ld ix,MonsterHeap.startOfHeap

.loop:
    ld a,(MonsterHeap.numActiveMonsters)
    cp 1
    jr z, .clearLastMonster

    ld a,(ix+1) ;;Load in health of current monster
    cp 0
    jr nz, .continue

.drawOverDeadMonster:
    ld h,(ix+2)
    ld l,(ix+3)
    dec l

    call getPathCoords
    ld de,cobbleTile
    call print8x8

    ld a,PAPER_WHITE
    or INK_BLACK
    call applyAttrAt

.decMonsterCount:
    ld iy,(MonsterHeap.locOfLastMonster)
    
    ld c,(iy)
    ld (ix),c

    ld c,(iy+1)
    ld (ix+1),c
    
    ld c,(iy+2)
    ld (ix+2),c

    ld c,(iy+3)
    ld (ix+3),c

    ld iy,MonsterHeap.locOfLastMonster
    dec (iy)
    dec (iy)
    dec (iy)
    dec (iy)

    ld iy, MonsterHeap.numActiveMonsters
    dec (iy)

    djnz .loop
    jr .exit

.continue
    inc ix
    inc ix
    inc ix
    inc ix
    djnz .loop
    jr .exit

.clearLastMonster:
    ;;If monster is not dead, jump to exit
    ld ix, MonsterHeap.startOfHeap
    ld a,(ix+1)
    cp 0
    jp nz, .exit

    ld h,(ix+2)
    ld l,(ix+3)
    dec l

    call getPathCoords
    ld de,cobbleTile
    call print8x8

    ld a,PAPER_WHITE
    or INK_BLACK
    call applyAttrAt

    ld iy,MonsterHeap.locOfLastMonster
    dec (iy)
    dec (iy)
    dec (iy)
    dec (iy)

    ld ix, MonsterHeap.numActiveMonsters
    dec (ix)

    ld h,(ix+2)
    ld l,(ix+3)
    dec l

.exit:
    pop hl
    pop de
    pop iy
    pop af
    pop bc
    pop ix
    ret

DrawMonsterHeap:
    push ix
    push af
    push bc
    push hl
    push de
    push iy

    ld ix, MonsterHeap.startOfHeap
    ld a, (MonsterHeap.numActiveMonsters)
    cp 0
    jp z, .exit

    ld b,a

.loop:
    ld h,(ix+2) ;;Id of path monster is on
    ld l,(ix+3) ;;Index on path monster is taking

    call getPathCoords ;Convert path info to coordinates
    ;;hl now has coords

    ;;If we are on the last coord, then the monster
    ;;is at the end of it's path
    ld de,(monsterPathOne) ;;
    sbc hl,de
    jr nz, .drawMonster

.killMonsterAtEndOfPath:
    ld (ix+1),0
    ld iy,CastleHP
    dec (iy)
    
.drawMonster:
    add hl,de
    ld de,skullTile
    call print8x8

    ld a,PAPER_WHITE
    or INK_RED
    call applyAttrAt

.reDrawOldLocation:
    ld h,(ix+2)
    ld l,(ix+3)
    dec l

    jp m, .continue

    call getPathCoords
    ld de,cobbleTile
    call print8x8

    ld a,PAPER_WHITE
    or INK_BLACK
    call applyAttrAt

.continue
    inc ix
    inc ix
    inc ix
    inc ix
    djnz .loop

.exit:
    pop iy
    pop de
    pop hl
    pop bc
    pop af
    pop ix
    ret

getPathCoords:
    push af
    push de

    ld de,hl
    inc de

.getPathInfoAddr:
    ld a,h
    cp 0
    jr z, .ldPathOne

    cp 1
    jr z, .ldPathTwo

.ldPathOne:
    ld hl, monsterPathOne.end 
    jr .addIndex

.ldPathTwo:
    ld hl, monsterPathTwo.end
    jr .addIndex

.addIndex:
    ld d,0
    sub hl,de
    sub hl,de
    ld de,(hl)
    ld hl,de

.exit:
    pop de
    pop af
    ret

UpdateMonsterPositions:
    push ix
    push bc
    push af

    ld a,(MonsterHeap.numActiveMonsters)
    cp 0
    jr z, .exit

    ld b,a

    ld ix,MonsterHeap.startOfHeap
.loop:
    inc (ix+3)

    inc ix
    inc ix
    inc ix
    inc ix
    djnz .loop

.exit:
    pop af
    pop bc
    pop ix
    ret


monsterPathOne:
    dw 0x1840
    dw 0x1848
    dw 0x1850
    dw 0x1858
    dw 0x2058
    dw 0x2858
    dw 0x3058
    dw 0x3858
    dw 0x4058
    dw 0x4858
    dw 0x5058
    dw 0x5060
    dw 0x5068
    dw 0x5070
    dw 0x5870
    dw 0x6070
    dw 0x6870
   
    dw 0x7070
    dw 0x7078
    dw 0x7080
    dw 0x7088
    dw 0x7090
    dw 0x7098
    dw 0x70A0
    dw 0x70A8
    dw 0x70B0

.end

monsterPathTwo:
    dw 0x1840
    dw 0x1848
    dw 0x1850
    dw 0x1858
    dw 0x2058
    dw 0x2858
    dw 0x3058
    dw 0x3858
    dw 0x4058
    dw 0x4858
    dw 0x5058
    dw 0x5060
    dw 0x5068
    dw 0x5070
    dw 0x5870
    dw 0x6070
    dw 0x6870
    dw 0x7070

    dw 0x7870
    dw 0x8070
    dw 0x8870
    dw 0x9070
    dw 0x9870
    dw 0xA070
    dw 0xA870
    dw 0xA868
    dw 0xA860
    dw 0xA858
    dw 0xB058
    dw 0xB858
    dw 0xC058
    dw 0xC858
    dw 0xD058
    dw 0xD858
    dw 0xE058
    dw 0xE858
    dw 0xF058
    dw 0xFF58
.end

MonsterHeap:
.locOfLastMonster:
    dw 0000h
.numActiveMonsters:
    db 00h
.startOfHeap

    savesna "out.sna",start