#!/usr/bin/env bash

set -euo pipefail

if [ "$#" -lt 1 ] ; then
  >&2 echo "Please provide a tag"
  exit 1
fi

tag=$1; shift 1;

submodules=(\
  freedom-metal \
  freedom-devicetree-tools \
  FreeRTOS-metal \
  scl-metal \
  scripts/cmsis-svd-generator \
  scripts/devicetree-overlay-generator \
  scripts/elf2hex \
  scripts/esdk-settings-generator \
  scripts/ldscript-generator \
  scripts/openocdcfg-generator \
)

set -x

for submodule in ${submodules[@]} ; do
  git -C ${submodule} tag ${tag}
  git -C ${submodule} push -f origin ${tag}
done
