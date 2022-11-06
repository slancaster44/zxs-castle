mainLoop:
    call monsterHandler
    call playerHandler

    call timeDelay
    jr mainLoop

DelayLength:
    dw 0xFFFF
timeDelay:
    push hl
    push af

    xor a 
    ld hl,(DelayLength) 

.loop:
    dec hl
    cp h
    jp nz,.loop
    cp l
    jp nz,.loop
    
.exit:
    pop af
    pop hl
    ret
