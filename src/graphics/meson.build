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

d_graphics_inc = include_directories('source')

d_graphics_src = [
	'source/aurorafw/graphics/package.d',
	'source/aurorafw/graphics/root.d',
	'source/aurorafw/graphics/api/context.d',
	'source/aurorafw/graphics/api/renderer.d',
	'source/aurorafw/graphics/api/opengl/context.d',
	'source/aurorafw/graphics/api/vulkan/context.d'
]

install_subdir('source/aurorafw/', install_dir: 'include/d/aurorafw/')

d_graphics_lib = library('aurorafw-graphics',
	d_graphics_src,
	include_directories: [d_graphics_inc],
	install: true,
	version: project_version,
	dependencies: [
		d_image_dep,
		d_gui_dep
	]
)

pkgc.generate(d_graphics_lib,
	name: 'aurorafw-graphics',
	subdirs: 'd/aurorafw',
	version: project_version,
	description: ''
)

d_graphics_dep = declare_dependency(
	link_with: [d_graphics_lib],
	include_directories: [d_graphics_inc],
	dependencies: [
		d_image_dep,
		d_gui_dep
	]
)

d_graphics_exe = executable('aurorafw-graphics-test',
	[d_graphics_src],
	include_directories: [d_graphics_inc],
	d_unittest: true,
	link_args: '-main',
	dependencies: [
		d_image_dep,
		d_gui_dep
	]
)

test('aurorafw-graphics-test', d_graphics_exe)
