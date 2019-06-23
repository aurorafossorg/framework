#!/usr/bin/env bash

set -e

dub $@
dub $@ :audio
dub $@ :cli
dub $@ :core
dub $@ :graphics
dub $@ :gui
dub $@ :image
dub $@ :jni
dub $@ :math
dub $@ :metadata
dub $@ :net
dub $@ :stdx
