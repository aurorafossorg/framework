#                                    / _|
#   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
#  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
# | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
#  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
#
# Copyright (C) 2018 Aurora Free Open Source Software.
#
# This file is part of the Aurora Free Open Source Software. This
# organization promote free and open source software that you can
# redistribute and/or modify under the terms of the GNU Lesser General
# Public License Version 3 as published by the Free Software Foundation or
# (at your option) any later version approved by the Aurora Free Open Source
# Software Organization. The license is available in the package root path
# as 'LICENSE' file. Please review the following information to ensure the
# GNU Lesser General Public License version 3 requirements will be met:
# https://www.gnu.org/licenses/lgpl.html .
#
# Alternatively, this file may be used under the terms of the GNU General
# Public License version 3 or later as published by the Free Software
# Foundation. Please review the following information to ensure the GNU
# General Public License requirements will be met:
# http://www.gnu.org/licenses/gpl-3.0.html.
#
# NOTE: All products, services or anything associated to trademarks and
# service marks used or referenced on this file are the property of their
# respective companies/owners or its subsidiaries. Other names and brands
# may be claimed as the property of others.
#
# For more info about intellectual property visit: aurorafoss.org or
# directly send an email to: contact (at) aurorafoss.org .

subdir('legacy')

subdir('core')
subdir('math')
subdir('audio')
subdir('image')
subdir('gui')
subdir('graphics')


d_inc = include_directories('source')

d_src = [
	'source/aurorafw/package.d'
]

install_subdir('source/aurorafw/', install_dir: 'include/d/aurorafw/')

d_lib = library('aurorafw',
	[d_src],
	include_directories: [d_inc],
	install: true,
	dependencies: [
		d_core_dep,
		d_math_dep,
		d_audio_dep,
		d_graphics_dep,
		d_image_dep,
		d_gui_dep
	],
	version: meson.project_version()
)

pkgc.generate(name: 'aurorafw',
	libraries: [d_lib],
	requires: ['aurorafw-core'],
	subdirs: 'd/aurorafw',
	version: meson.project_version(),
	description: ''
)

d_dep = declare_dependency(
	link_with: [d_lib],
	include_directories: [d_inc],
	dependencies: [
		d_core_dep,
		d_math_dep,
		d_audio_dep,
		d_graphics_dep,
		d_image_dep,
		d_gui_dep
	]
)

#d_exe = executable('aurorafw-test',
#	[d_src],
#	include_directories: [d_inc],
#	dependencies: [d_core_dep, d_math_dep],
#	d_unittest: true,
#	link_args: '-main'
#)

#test('aurorafw-test', d_exe)