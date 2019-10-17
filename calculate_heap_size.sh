#!/usr/bin/env bash

# this script is for freedom e-sdk compile flow
# in order to decide heap size based on ram size

set -eo pipefail

#get linker script from LDFLAGS "-T" option

while getopts ":T:" OPTION
do

    case $OPTION in
        T)
            T_ARGS=$OPTARG
            ;;
        ?) continue ;;
    esac


done

if [[ -z $T_ARGS ]]; then
    exit 0
fi

#extract ram size from linker script

RAMSIZE=`sed -n  's/.*ram .*ORIGIN .*LENGTH = \(.*\)/\1/p' $T_ARGS`

# for ram size over than 128M, we just give it a little bit more than 128M
# for ram size lower than 128M, we need to preserve around 1084 for
# freedom metal .data, .bss and .stack

FINAL_HEAP=$(((RAMSIZE -10984)<134217728 ? (RAMSIZE - 10984):134227712))

# we also need to preserve around 8488 for libnano.c extract allocation

HEAP_REMOVE_RESERVE=$((FINAL_HEAP - 8488))

#after remove all reservation space, we can actual calculate the RANGE
#for latency testing

RANGE=1024
while ((($RANGE << 1) < $HEAP_REMOVE_RESERVE )); do
    RANGE=$((RANGE << 1))
done


#range represent unit is KB (right shift by 10)
RANGE=$((RANGE >> 10))

#the range will be min( approximate HEAP_REMOVE_RESERVE , 128MB )

FINAL_RANGE=$((RANGE>131072 ? 131072 : RANGE ))

echo $FINAL_HEAP $FINAL_RANGE

