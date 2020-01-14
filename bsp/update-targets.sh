#!/bin/bash

help() {
    cat >&2 <<EOF
$0: BSP Generator for the SiFive Freedom E SDK
    --help                     Prints this help text.
    --target-name              Specify bsp target name.
    --target-type              Specify bsp target type [rtl | arty | vc707].
    --sdk-path=*               The path to the freedom-e-sdk clone directory, public or private.
    --target-dts=*.dts         The path to the target device tree that will be used.
EOF
}

warn () {
    echo "$0:" "$@" >&2
}
die () {
    shift
    warn "$@"
    exit 1
}

unset DTSFILE
unset CUSTOM_PATH
unset CUSTOM_NAME
unset NO_FIXUP
NO_FIXUP=0
while [ "$1" != "" ]
do
    case "$1" in
    --help)               help "$0";                                 exit 0;;
    --no-fixup)           NO_FIXUP=1;                                shift 1;;
    --target-name)        CUSTOM_NAME="$2";                          shift 2;;
    --target-type)        CUSTOM_TYPE="$2";                          shift 2;;
    --sdk-path=*)         CUSTOM_PATH="$(echo "$1" | cut -d= -f2-)"; shift 1;;
    --sdk-path)           CUSTOM_PATH="$2";                          shift 2;;
    --target-dts=*)       DTSFILE="$(echo "$1" | cut -d= -f2-)";     shift 1;;
    --target-dts)         DTSFILE="$2";                              shift 2;;
    *) echo "$0: Unknown argument $1" >&2;                        exit 1;;
    esac
done

if [ "$CUSTOM_PATH" == "" -a "$CUSTOM_NAME" == "" -a "$DTSFILE" == "" ]
then
    TARGET_LIST="$(ls -d */) "
else
    file "$DTSFILE"
    if [ ! -f "$DTSFILE" ]
    then
        echo "[ERROR] $0: $DTSFILE must be a file" >&2
        help "$0"
        exit 1
    fi
    if [ "$CUSTOM_NAME" == "" ]
    then
        echo "[ERROR] $0: --target-name is mandatory" >&2
        help "$0"
        exit 1
    fi
    if [ "$CUSTOM_TYPE" == "" ]
    then
        echo "[INFO] $0: --target-type is not given! Default to rtl" >&2
        TARGET_TYPE="rtl"
    else
        TARGET_TYPE="$CUSTOM_TYPE"
    fi
    CUSTOM_TARGET="$CUSTOM_PATH/bsp/$CUSTOM_NAME"
    if [ ! -d "$CUSTOM_TARGET" ]
    then
        echo "[INFO] $0: "$CUSTOM_TARGET" not found! Creating one" >&2
	mkdir -p $CUSTOM_TARGET
    fi
    cp $DTSFILE "$CUSTOM_TARGET/design.dts"
    TARGET_LIST="$CUSTOM_TARGET "
fi

OVERLAY_GENERATOR=../scripts/devicetree-overlay-generator/generate_overlay.py

DTC=dtc
MEE_HEADER_GENERATOR=freedom-metal_header-generator
LDSCRIPT_GENERATOR=../scripts/ldscript-generator/generate_ldscript.py
MAKEATTRIB_GENERATOR=freedom-makeattributes-generator
BARE_HEADER_GENERATOR=freedom-bare_header-generator
OPENOCDCFG_GENERATOR=freedom-openocdcfg-generator

CORE_DTS_FILENAME=core.dts
DESIGN_DTS_FILENAME=design.dts
DTB_FILENAME=temp.dtb
HEADER_FILENAME=metal.h
LDS_DEFAULT_FILENAME=metal.default.lds
LDS_RAMRODATA_FILENAME=metal.ramrodata.lds
LDS_SCRATCHPAD_FILENAME=metal.scratchpad.lds
SETTINGS_FILENAME=settings.mk
BARE_HEADER_FILENAME=metal-platform.h
OPENOCDCFG_FILENAME=openocd.cfg
OPENOCDCFG_CJTAG_FILENAME=openocd.cjtag.cfg

update_target() {
    TARGET=$1
    if [ "$TARGET_TYPE" == "" ]; then
        TARGET_TYPE=$TARGET
    fi

    echo "Updating target $TARGET"

    # Generate overlay
    if [ $NO_FIXUP -ne 1 ]; then
        echo "Generating overlay $TARGET/$DESIGN_DTS_FILENAME"
        . ../venv/bin/activate && $OVERLAY_GENERATOR --type $TARGET_TYPE --output $TARGET/$DESIGN_DTS_FILENAME --rename-include $CORE_DTS_FILENAME $TARGET/$CORE_DTS_FILENAME
    fi

    # Compile temporary .dtb
    $DTC -I dts -O dtb -o $TARGET/$DTB_FILENAME $TARGET/$DESIGN_DTS_FILENAME || warn "Failed to compile $TARGET/$DESIGN_DTS_FILENAME to dtb"

    # Produce parameterized files
    pushd $TARGET && $MEE_HEADER_GENERATOR -d $DTB_FILENAME -o $HEADER_FILENAME || warn "Failed to produce $TARGET/$HEADER_FILENAME" && popd
    . ../venv/bin/activate && $LDSCRIPT_GENERATOR -d $TARGET/$DESIGN_DTS_FILENAME -o $TARGET/$LDS_DEFAULT_FILENAME || warn "Failed to produce $TARGET/$LDS_DEFAULT_FILENAME"
    . ../venv/bin/activate && $LDSCRIPT_GENERATOR -d $TARGET/$DESIGN_DTS_FILENAME -o $TARGET/$LDS_RAMRODATA_FILENAME --ramrodata || warn "Failed to produce $TARGET/$LDS_RAMRODATA_FILENAME"
    . ../venv/bin/activate && $LDSCRIPT_GENERATOR -d $TARGET/$DESIGN_DTS_FILENAME -o $TARGET/$LDS_SCRATCHPAD_FILENAME --scratchpad || warn "Failed to produce $TARGET/$LDS_SCRATCHPAD_FILENAME"
    pushd  $TARGET && $MAKEATTRIB_GENERATOR -d $DTB_FILENAME -b $TARGET_TYPE -o $SETTINGS_FILENAME || warn "Failed to produce $TARGET/$SETTINGS_FILENAME" && popd
    pushd  $TARGET && $BARE_HEADER_GENERATOR -d $DTB_FILENAME -o $BARE_HEADER_FILENAME || warn "Failed to produce $TARGET/$BARE_HEADER_FILENAME" && popd

    if [[ "$TARGET_TYPE" =~ "arty" || "$TARGET_TYPE" =~ "vc707" || "$TARGET_TYPE" =~ "hifive" ]] ; then
        if [ `grep -c "jlink" $TARGET/$SETTINGS_FILENAME` -ne 1 ] ; then
            echo "generating $OPENOCDCFG_FILENAME"
            $OPENOCDCFG_GENERATOR -d $TARGET/$DTB_FILENAME -b $TARGET_TYPE -o $TARGET/$OPENOCDCFG_FILENAME || warn "Failed to produce $TARGET/$OPENOCDCFG_FILENAME"
        fi
    fi
    if [[ "$TARGET_TYPE" =~ "arty" ]] ; then
        echo "generating $OPENOCDCFG_CJTAG_FILENAME"
        $OPENOCDCFG_GENERATOR -d $TARGET/$DTB_FILENAME -p cjtag -b $TARGET_TYPE -o $TARGET/$OPENOCDCFG_CJTAG_FILENAME || warn "Failed to produce $TARGET/$OPENOCDCFG_CJTAG_FILENAME"
    fi

    # Remove temporary .dtb
    rm $TARGET/$DTB_FILENAME

    TARGET_TYPE=""
    echo ""
}

if [ $NO_FIXUP -ne 1 ]; then
    echo "Generating overlay $TARGET/$DESIGN_DTS_FILENAME"
    python3 -m venv ../venv
    . ../venv/bin/activate && pip install --upgrade pip
    . ../venv/bin/activate && pip install -r ../requirements.txt
fi

for TARGET in $TARGET_LIST
do
    update_target $TARGET
done

