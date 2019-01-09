#!/bin/bash

set -e
set -o pipefail

unset example
unset out
while [[ "$1" != "" ]]
do
	case "$1"
	in
	--example)	example="$2";		shift 2;;
	--out)		out="$2";		shift 2;;
	*) echo "$0: Unknown argument $1";	exit 1;;
	esac
done


if [[ "$example" == "" ]]
then
	echo "$0: --example is required" >&2
	exit 1
fi

if [[ "$out" == "" ]]
then
	echo "$0: --out is required" >&2
	exit 1
fi

# Check if the example exists

if ! [ -d software/$example ]
then
	echo "$0: $example does not refer to a valid example project" >&2
	exit 1
fi

# Make the output directory

mkdir -p software/$out

# Copy the source file and rename

cp software/$example/$example.c software/$out/$out.c

# Copy the makefile and replace the example name with the output name

cp software/$example/Makefile software/$out/Makefile

sed -i -e "s/$example/$out/g" software/$out/Makefile

# Create a new .gitignore with the output name

echo $out > software/$out/.gitignore

