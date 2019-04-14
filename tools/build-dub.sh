#!/usr/bin/env bash

dub build $@
dub build :android $@
dub build :audio $@
dub build :cli $@
dub build :core $@
dub build :graphics $@
dub build :gui $@
dub build :image $@
dub build :jni $@
dub build :math $@
dub build :metadata $@
dub build :net $@
dub build :stdx $@
