/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
**
** This file is part of the Aurora Free Open Source Software. This
** organization promote free and open source software that you can
** redistribute and/or modify under the terms of the GNU Lesser General
** Public License Version 3 as published by the Free Software Foundation or
** (at your option) any later version approved by the Aurora Free Open Source
** Software Organization. The license is available in the package root path
** as 'LICENSE' file. Please review the following information to ensure the
** GNU Lesser General Public License version 3 requirements will be met:
** https://www.gnu.org/licenses/lgpl.html .
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3 or later as published by the Free Software
** Foundation. Please review the following information to ensure the GNU
** General Public License requirements will be met:
** http://www.gnu.org/licenses/gpl-3.0.html.
**
** NOTE: All products, services or anything associated to trademarks and
** service marks used or referenced on this file are the property of their
** respective companies/owners or its subsidiaries. Other names and brands
** may be claimed as the property of others.
**
** For more info about intellectual property visit: aurorafoss.org or
** directly send an email to: contact (at) aurorafoss.org .
*****************************************************************************/

#ifndef AURORAFW_AURORA_H
#define AURORAFW_AURORA_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

// Core
#include <AuroraFW/Core/Application.h>
#include <AuroraFW/Core/DebugManager.h>

// Standard Library

// CoreLib
#include <AuroraFW/CoreLib/String.h>
#include <AuroraFW/CoreLib/CircularShift.h>
#include <AuroraFW/CoreLib/Target.h>
#include <AuroraFW/CoreLib/Type.h>
#include <AuroraFW/CoreLib/Endian.h>
#include <AuroraFW/CoreLib/MemoryManager.h>
#include <AuroraFW/CoreLib/Allocator.h>

#ifndef AFW__PHC

	// Audio
	#include <AuroraFW/Audio/AudioInput.h>
	#include <AuroraFW/Audio/AudioOutput.h>
	#include <AuroraFW/Audio/AudioBackend.h>
	#include <AuroraFW/Audio/AudioUtils.h>

	// Crypto
	#include <AuroraFW/Crypto/AES.h>

	// GUI
	#include <AuroraFW/GUI/Window.h>
	#include <AuroraFW/GUI/Label.h>
	#include <AuroraFW/GUI/Button.h>
	#include <AuroraFW/GUI/Application.h>

	// Shell
	#include <AuroraFW/CLI/Log.h>
	#include <AuroraFW/CLI/Color.h>
	#include <AuroraFW/CLI/Output.h>
	#include <AuroraFW/CLI/Input.h>

	// I/O
	#include <AuroraFW/IO/File.h>
	#include <AuroraFW/IO/Timer.h>
	#include <AuroraFW/IO/Info/Memory.h>
	#include <AuroraFW/IO/Info/System.h>

	//OpenGL
	#include <AuroraFW/GEngine/GL/Global.h>
	#include <AuroraFW/GEngine/GL/OpenGL.h>
	#include <AuroraFW/GEngine/GL/GL.h>
	#include <AuroraFW/GEngine/GL/RTShader.h>
	#include <AuroraFW/GEngine/GL/RTShaderPipeline.h>
	#include <AuroraFW/GEngine/GL/Buffer.h>
	#include <AuroraFW/GEngine/GL/VertexArray.h>

	//GEngine
	#include <AuroraFW/GEngine/Application.h>
	#include <AuroraFW/GEngine/Window.h>
	#include <AuroraFW/GEngine/API/Context.h>
	#include <AuroraFW/GEngine/Input.h>
	#include <AuroraFW/GEngine/AssetManager.h>
	#include <AuroraFW/GEngine/AssetType.h>
	//GEngine API
	#include <AuroraFW/GEngine/API/Context.h>
	#include <AuroraFW/GEngine/API/Texture.h>
	#include <AuroraFW/GEngine/API/Renderer.h>

	//Math
	#include <AuroraFW/Math/Vector2D.h>
	#include <AuroraFW/Math/Vector3D.h>
	#include <AuroraFW/Math/Vector4D.h>
	#include <AuroraFW/Math/Matrix.h>
	#include <AuroraFW/Math/Algorithm.h>
	#include <AuroraFW/Math/Utils.h>

	//Image
	#include <AuroraFW/Image/Image.h>
	#include <AuroraFW/Image/BaseColor.h>
#endif

#endif // AURORAFW_AURORA_H
