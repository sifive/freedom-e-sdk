#!/bin/bash

set -e
set -o pipefail

unset elf
unset hex
unset cfg
unset openocd
unset jlink
unset gdb
while [[ "$1" != "" ]]
do
    case "$1"
    in
    --elf)                 elf="$2";     shift 2;;
    --hex)                 hex="$2";     shift 2;;
    --openocd)             openocd="$2"; shift 2;;
    --openocd-config)      cfg="$2";     shift 2;;
    --jlink)               jlink="$2";   shift 2;;
    --gdb)                 gdb="$2";     shift 2;;
    *) echo "$0: Unknown argument $1";   exit 1;;
    esac
done

if [ "$elf" == "" -a "$hex" == "" ]
then
    echo "$0: --elf or --hex is required" >&2
    exit 1
fi

export GDB_PORT=3333

if [ "$jlink" != "" ]
then

echo -e "loadfile $hex\nrnh\nexit" | $jlink -device FE310 -if JTAG -speed 4000 -jtagconf -1,-1 -autoconnect 1

else

$openocd -f $cfg &

$gdb $elf --batch -ex "set remotetimeout 240" -ex "target extended-remote localhost:${GDB_PORT}" -ex "monitor reset halt" -ex "monitor flash protect 0 64 last off" -ex "thread apply all set \$pc=_enter" -ex "load" -ex "monitor resume" -ex "monitor shutdown" -ex "quit"

kill %1

fi
