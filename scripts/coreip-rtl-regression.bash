#!/bin/bash

set -e
set -o pipefail
set -x

boards=()
boards+=("coreip-e31")
boards+=("coreip-s51")

programs=()
programs+=("hello")

for board in "${boards[@]}"
do
    # This avoids a multidimmensional associtave array, which bash doesn't
    # appear to enjoy.
    releases=()
    case "$board"
    in
    "coreip-e31") releases=("sifive_coreip_E31_AHB_rtl_full_v3p0_rc1") ;;
    "coreip-s51") releases=("sifive_coreip_E51_TL_rtl_full_v3p0_rc0")  ;;
    *) echo "$0: unknown board $board"; exit 1;;
    esac

    for release in "${releases}"
    do
        coreip_wdir="$(echo "$release" | cut -d_ -f1-6)"
        coreip_tdir="$(echo "$release" | cut -d_ -f1-7)"
        coreip_tar="/work/coreplex/${coreip_wdir}/${release}/${coreip_tdir}.tar.gz"

        for program in "${programs[@]}"
	do
            make BSP=mee BOARD="${board}" PROGRAM="${program}" clean
            make BSP=mee BOARD="${board}" PROGRAM="${program}" software
            rm -rf "${coreip_dir}"
            tar -xvzpf "${coreip_tar}"
            mkdir -p "${coreip_tdir}"/tests/"${program}"
            cp software/"${program}"/"${program}".hex "${coreip_tdir}"/tests/"${program}"/program.hex
            make -C "${coreip_tdir}" "${program}".out
	done
    done
done
