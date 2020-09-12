#!/usr/bin/env bash

set -e

dub "$@"
if [ "$1" == "test" ]; then
	exit 0
fi

coverage_tmp_folder=".dub-coverage"

if [[ "$*" == *"--coverage"* ]]
then
	mkdir -p $coverage_tmp_folder
	DUB_COVERAGE="1"
fi

exit_trap() {
    if [[ $DUB_COVERAGE == "1" ]]
	then
		USELESS_DUB_COVERAGE_OUTPUT="
-home-
-root-
-tmp-
"
		for useless in $USELESS_DUB_COVERAGE_OUTPUT; do
			rm -rf -- "$useless"*.lst
		done

		mv -f "$coverage_tmp_folder"/* .
		rm -rf "$coverage_tmp_folder"
	fi
}

trap exit_trap EXIT

PACKAGES="$(find src -mindepth 1 -maxdepth 1 -type d | grep -v -E "unit$|source$")"

for subprojects in $PACKAGES; do
	dub "$@" ":$(basename "$subprojects")"
	if [[ "$DUB_COVERAGE" == "1" ]]
	then
		mv "$(echo "$subprojects" | tr '/' '-')-"*.lst "$coverage_tmp_folder"
	fi
done
