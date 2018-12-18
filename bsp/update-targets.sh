#!/usr/bin/env sh

DTC=dtc
MEE_HEADER_GENERATOR=freedom-mee_header-generator
LDSCRIPT_GENERATOR=freedom-ldscript-generator

DTS_FILENAME=design.dts
DTB_FILENAME=temp.dtb
HEADER_FILENAME=mee.h
LDSCRIPT_FILENAME=mee.lds

TARGET_LIST="$(ls coreip* -d) "
TARGET_LIST+="sifive-hifive1 freedom-e310-arty "

update_target() {
    TARGET=$1

    echo "Updating target $TARGET"
    
    # Compile temporary .dtb
    $DTC -I dts -O dtb -o $TARGET/$DTB_FILENAME $TARGET/$DTS_FILENAME || die "Failed to compile $TARGET/$DTS_FILENAME to dtb"

    # Produce parameterized files
    $MEE_HEADER_GENERATOR -d $TARGET/$DTB_FILENAME -o $TARGET/$HEADER_FILENAME || die "Failed to produce $TARGET/$HEADER_FILENAME"
    $LDSCRIPT_GENERATOR -d $TARGET/$DTB_FILENAME -l $TARGET/$LDSCRIPT_FILENAME || die "Failed to produce $TARGET/$LDSCRIPT_FILENAME"

    # Remove temporary .dtb
    rm $TARGET/$DTB_FILENAME

    echo ""
}

for TARGET in $TARGET_LIST
do
    update_target $TARGET
done

