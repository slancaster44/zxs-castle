    org 8000h
    device zxspectrum48
    include "asset_binary.inc"
    include "zxs_consts.inc"
    include "getPixelAddr.inc"
    include "mkScreenBlack.inc"
    include "batchPaint.inc"
    include "paintLandscape.inc"
    include "print8x8.inc"
    include "mainLoop.inc"
    include "playerHandler.inc"

start:
    im 1
    ld sp,USER_RAM_END

    call CLR_SCREEN
    call mkScreenBlack
    call paintCastle
    call paintRoad
    call paintGrass
    call paintHorizon

    ld c,1
    ld d,03h
    ld e,1
    call AllocMonster

    ld c,2
    ld d,05h
    ld e,0
    call AllocMonster
    
    call mainLoop

    include "monster.inc"
