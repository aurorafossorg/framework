#                                    / _|
#   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
#  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
# | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
#  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
#
# Copyright (C) 2018-2019 Aurora Free Open Source Software.
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

d_gui_inc = include_directories('source')

d_gui_src = [
	'source/aurorafw/gui/package.d',
	'source/aurorafw/gui/window.d',
	'source/aurorafw/gui/api/backend.d',
	'source/aurorafw/gui/platform/x11/package.d',
	'source/aurorafw/gui/platform/x11/x.d',
	'source/aurorafw/gui/platform/x11/xlib.d',
	'source/aurorafw/gui/platform/x11/xresource.d',
	'source/aurorafw/gui/platform/x11/xutil.d',
	'source/aurorafw/gui/platform/x11/extensions/xf86vmode.d',
	'source/aurorafw/gui/platform/x11/xcursor/dynload.d',
	'source/aurorafw/gui/platform/x11/xcursor/package.d',
	'source/aurorafw/gui/platform/x11/xcursor/types.d',
	'source/aurorafw/gui/platform/x11/xcursor/xcursor.d',
	'source/aurorafw/gui/api/x11/backend.d',
	'source/aurorafw/gui/api/x11/window.d',
	'source/aurorafw/gui/api/wayland/window.d',
	'source/aurorafw/gui/api/wayland/backend.d'
]

install_subdir('source/aurorafw/', install_dir: 'include/d/aurorafw/')

x11_dep = dependency('x11', required : true)

d_gui_lib = library('aurorafw-gui',
	d_gui_src,
	include_directories: [d_gui_inc],
	install: true,
	version: project_version,
	dependencies: [
		d_math_dep,
		d_core_dep,
		x11_dep
	]
)

pkgc.generate(d_gui_lib,
	name: 'aurorafw-gui',
	subdirs: 'd/aurorafw',
	version: project_version,
	description: ''
)

d_gui_dep = declare_dependency(
	link_with: [d_gui_lib],
	include_directories: [d_gui_inc],
	dependencies: [
		d_math_dep,
		d_core_dep,
		x11_dep
	]
)

d_gui_exe = executable('aurorafw-gui-test',
	[d_gui_src],
	d_unittest: true,
	link_args: '-main',
	include_directories: [d_gui_inc],
	dependencies: [
		d_math_dep,
		d_core_dep,
		x11_dep
	]
)

test('aurorafw-gui-test', d_gui_exe)
