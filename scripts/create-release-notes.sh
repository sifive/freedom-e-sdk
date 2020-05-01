#!/bin/bash
# Copyright (c) 2020 SiFive Inc.
# SPDX-License-Identifier: Apache-2.0

set -euo pipefail

if [ "$#" -lt 2 ] ; then
  >&2 echo "$0: please provide project name and release tag"
  exit 1
fi

project=$1; shift 1;
current_release=$1; shift 1;

# Get the most recent previous tag with git-describe. If this is
# the first tag in the repository, then this will return a commit
# hash (because of the --always flag).
last_release=$(git describe --tags --always HEAD~)

echo "# Release notes for ${project} ${current_release}"
echo "## Statistics since ${last_release}"
echo "- $(git rev-list --count ${last_release}..HEAD) commits"
echo "-$(git diff --shortstat ${last_release} HEAD)"
echo ""
echo "## Authors"
git shortlog -s -n --no-merges ${last_release}..HEAD | cut -f 2
echo ""
echo "## Merge history"
git log --merges --pretty=format:"%h %b" ${last_release}..HEAD
