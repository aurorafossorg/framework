#!/usr/bin/env bash

set -e

dub $@

for subprojects in $(find src -type f -name dub.json -exec dirname {} +); do
	pushd $subprojects > /dev/null
	dub $@
	popd > /dev/null
done
