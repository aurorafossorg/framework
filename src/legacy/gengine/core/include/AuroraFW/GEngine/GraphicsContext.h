/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
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

#ifndef AURORAFW_GENGINE_GRAPHICSCONTEXT_H
#define AURORAFW_GENGINE_GRAPHICSCONTEXT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/Window.h>
#include <AuroraFW/GEngine/API/Context.h>
#include <AuroraFW/GEngine/API/Renderer.h>
#include <AuroraFW/Core/InputListener.h>
#include <AuroraFW/IO/Timer.h>
#include <AuroraFW/GEngine/ImGui/Loader.h>
#include <AuroraFW/GEngine/Root.h>

#include <set>

namespace AuroraFW {
	namespace GEngine {
		class AFW_API GraphicsContext {
		public:
			GraphicsContext(std::string , const API::RenderAPI& = API::OpenGL, WindowProperties = {});
			GraphicsContext(std::string , const char* );
			virtual ~GraphicsContext();

			void renderLoop();

			virtual void onRender() {}
			virtual void onDestroy() {}
			void addInputListener(InputListener *);

			inline float getFramerate() { return 1000.0f / _tpf; }
			AFW_FORCE_INLINE float getTPF() { return _tpf; }
			AFW_FORCE_INLINE const Window* getWindow() const { return _window; }

			struct DebugInfo {
				std::vector<float> framerate;
			};
			static void renderDebugGUI(const DebugInfo& );
			void renderDebugGUI();

		protected:
			Root* root;

		private:
			void _internalRender();

			Window* _window;
			std::unique_ptr<ImGuiLoader> _guiLoader;
			std::set<InputListener*> _listeners;
			std::array<float, 64> _frameratebuf;
			float _tpf;
			IO::Timer _frametimer = IO::Timer();
			IO::Timer _framerateTimer = IO::Timer();
			bool _isdebuggui;
		};
	}
}

#endif // AURORAFW_GENGINE_GRAPHICSCONTEXT_H
