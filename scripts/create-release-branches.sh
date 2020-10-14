#!/usr/bin/env bash
set -euo pipefail
if [ "$#" -lt 2 ] ; then
  >&2 echo "Please provide a tag and branch"
  exit 1
fi
tag=$1; shift 1;
branch=$1; shift 1;
echo "Creating release branch ${branch} based on tag ${tag}"
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
  git -C ${submodule} checkout ${tag}
  git -C ${submodule} checkout -b ${branch}
  git -C ${submodule} push -u origin ${branch}
done
