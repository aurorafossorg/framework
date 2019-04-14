#!/usr/bin/env bash

set -e

pushd examples

dub build
dub test

PACKAGES="
audio-cli_player
gui-simple_window
metadata-detect_files
metadata-pdf_tests
"

for files in $PACKAGES; do
	dub build :$files
	dub test :$files
done

popd
