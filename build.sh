#!/bin/bash
rm -r bin/out*
sjasmplus $1 --fullpath \
    --sld=./bin/out.sld \
    --lst=./bin/out.lst \
     --outprefix=./bin/ \
     --inc=./inc