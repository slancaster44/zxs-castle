
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
    dw 0x7078
    dw 0x7080
    dw 0x7088
    dw 0x7090
    dw 0x7098
    dw 0x70A0
    dw 0x70A8
    dw 0x70B0
    dw 0x70B8

    dw 0x7870
    dw 0x8070
    dw 0x8870
    dw 0x9070
    dw 0x9870
    dw 0xA070
    dw 0xA870
    dw 0xB070
    dw 0xB870
    dw 0xB868
    dw 0xB860
    dw 0xB858
    dw 0xB850
    dw 0xB848
    dw 0xB840
    dw 0xB838
    dw 0xB830
    dw 0xB828
    dw 0xC028
    dw 0xC828
    dw 0xC820
    dw 0xC818
    dw 0xC810
    dw 0xC808
    dw 0xD028
    dw 0xD828
    dw 0xE028
    dw 0xE828
    dw 0xF028
    dw 0xFF28
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
    dw 0xF050
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