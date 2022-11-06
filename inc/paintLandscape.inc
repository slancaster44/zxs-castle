
castleCoords:
    dw 0x0000
    dw 0x1000
    dw 0x2000
    dw 0x3000

    dw 0x0008
    dw 0x0808
    dw 0x1008
    dw 0x1808
    dw 0x2008
    dw 0x2808
    dw 0x3008

    dw 0x0810
    dw 0x1010
    dw 0x1810
    dw 0x2010
    dw 0x2810

    dw 0x0818
    dw 0x1018
    dw 0x1818
    dw 0x2018
    dw 0x2818

    dw 0x0820
    dw 0x1020
    dw 0x1820
    dw 0x2020
    dw 0x2820

    dw 0x0828
    dw 0x1028
    dw 0x1828
    dw 0x2028
    dw 0x2828

    dw 0x0830
    dw 0x1030
    dw 0x2030
    dw 0x2830

    dw 0x0838
    dw 0x1038
    dw 0x2038
    dw 0x2838
.end

castleDoorCoords:
    dw 0x1830
    dw 0x1838
.end

paintCastle:
    ld de,cobbleTile
    ld ix,castleCoords
    ld bc,castleCoords.end
    call batchPaint

    ld de,barTile
    ld ix,castleDoorCoords
    ld bc,castleDoorCoords.end
    call batchPaint

    ld a,PAPER_RED
    or INK_YELLOW
    ld ix,castleDoorCoords
    ld bc,castleDoorCoords.end
    call batchAttr
    ret

roadCoords:
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

    dw 0x7078
    dw 0x7080
    dw 0x7088
    dw 0x7090
    dw 0x7098
    dw 0x70A0
    dw 0x70A8
    dw 0x70B0


.end
paintRoad:
    ld de,cobbleTile
    ld ix,roadCoords
    ld bc,roadCoords.end
    call batchPaint

    ld a,PAPER_WHITE
    or INK_BLACK
    ld ix,roadCoords
    ld bc,roadCoords.end
    call batchAttr
    ret

grassCoords:
    dw 0x5840
    dw 0xF048
    dw 0x2890
    dw 0xD080
.end

paintGrass:
    ld de,grassTile
    ld ix,grassCoords
    ld bc, grassCoords.end
    call batchPaint

    ld a,PAPER_BLACK
    or INK_GREEN
    ld ix,grassCoords
    ld bc,grassCoords.end
    call batchAttr

    ret

horizonCoords:
    dw 0x0030
    dw 0x3030
    dw 0x3830
    dw 0x4030
    dw 0x4830
    dw 0x5030
    dw 0x5830
    dw 0x6030
    dw 0x6830
    dw 0x7030
    dw 0x7830
    dw 0x8030
    dw 0x8830
    dw 0x9030
    dw 0x9830
    dw 0xA030
    dw 0xA830
    dw 0xB030
    dw 0xB830
    dw 0xC030
    dw 0xC830
    dw 0xD030
    dw 0xD830
    dw 0xE030
    dw 0xE830
    dw 0xF030
    dw 0xFF30
.end

paintHorizon:
    ld de,grassSurface
    ld ix,horizonCoords
    ld bc,horizonCoords.end
    call batchPaint

    ld de,grassSurface
    ld ix,horizonCoords
    ld bc,horizonCoords.end
    call batchAttr

    ret