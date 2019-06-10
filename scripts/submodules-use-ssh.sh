#!/bin/bash

# By default, when you clone Freedom E SDK, submodules are instantiated with their
# origin URLs pointing to GitHub's HTTPS URL for the repository.

# If you're a collaborator of this repository, it's annoying to update all the
# submodule URLs so that you can push to the repositories. This script fixes that
# by changing all the submodules to use SSH instead of HTTPS. If you're not a
# collaborator, don't bother using this script unless you really want to authenticate
# to GitHub with SSH for some reason.

set -e
set -o pipefail

SUBMODULE_PATHS=`grep -o "path = .*$" .gitmodules | cut -d ' ' -f 3`

for SUBMODULE in $SUBMODULE_PATHS ; do 
    pushd $SUBMODULE > /dev/null

    OLD_URL=`git remote get-url origin`

    NEW_URL=`echo $OLD_URL | sed -e 's/https:\/\/github.com\//git@github.com:/'`

    echo "Updating URL for $SUBMODULE from $OLD_URL to $NEW_URL"

    git remote set-url origin $NEW_URL
    
    popd > /dev/null
done

