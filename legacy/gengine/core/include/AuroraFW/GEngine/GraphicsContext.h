/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

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
