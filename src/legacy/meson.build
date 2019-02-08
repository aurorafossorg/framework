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

add_global_arguments('-std=c++17', language : 'cpp')

legacy_stdl_inc = include_directories('stdl/include')
legacy_corelib_inc = include_directories('corelib/include')
legacy_core_inc = include_directories('core/include')
legacy_cli_inc = include_directories('cli/include')

legacy_gengine_core_inc = include_directories('gengine/core/include')
legacy_gengine_vulkan_inc = include_directories('gengine/vulkan/include')
legacy_gengine_opengl_inc = include_directories('gengine/opengl/include')

subdir('stdl')
subdir('core')
subdir('corelib')
subdir('cli')
subdir('math')
subdir('audio')
subdir('crypto')
subdir('image')
subdir('io')
subdir('gui')
subdir('gengine')
subdir('netsocks')
#subdir('parser')

aurorafw_legacy_dep = declare_dependency(
	dependencies: [
		legacy_gengine_core_dep,
		legacy_audio_dep,
		legacy_cli_dep,
		legacy_image_dep,
		legacy_core_dep,
		legacy_corelib_dep,
		legacy_stdl_dep,
		legacy_crypto_dep,
		legacy_gui_dep,
		legacy_io_dep,
		legacy_math_dep,
		legacy_netsocks_dep
	]
)