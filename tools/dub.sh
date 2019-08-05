#!/usr/bin/env bash

set -e

dub $@

PACKAGES="
core
cli
math
audio
image
graphics
gui
net
metadata
stdx
"

for subprojects in $PACKAGES; do
	dub $@ :$subprojects
done

if [ "$1" == "test" ]; then
	dub $@ :unit
fi
