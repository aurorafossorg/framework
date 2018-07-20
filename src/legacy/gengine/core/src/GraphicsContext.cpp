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

#include <AuroraFW/GEngine/GraphicsContext.h>

#include <AuroraFW/CoreLib/Callback.h>
#include <AuroraFW/GEngine/Input.h>

namespace AuroraFW {
	namespace GEngine {
		GraphicsContext::GraphicsContext(std::string name, const API::RenderAPI& api, WindowProperties wp)
		{
			API::Context::setRenderAPI(api);

			wp.vsync = false;
			_window = AFW_NEW Window(name, wp);
			root = AFW_NEW Root;
			root->inputHandler = std::make_unique<InputManager>(_window);
			root->addRenderer(API::Renderer::Load());
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			_guiLoader = std::unique_ptr<GEngine::ImGuiLoader>(GEngine::ImGuiLoader::Load(_window, root->inputHandler.get()));
			_frameratebuf.fill(0.0f);
		}

		GraphicsContext::GraphicsContext(std::string name, const char* path)
		{
			//if(path == AFW_NULLPTR)
		}

		GraphicsContext::~GraphicsContext()
		{
			delete root;
			delete _window;
		}

		void GraphicsContext::renderDebugGUI()
		{
			_isdebuggui = true;
			ImGui::Begin("Debug");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / _frameratebuf.back(), _frameratebuf.back());
			ImGui::PlotLines("FPS", _frameratebuf.data(), _frameratebuf.size(), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(300,50));
			ImGui::Text("%d vertices, %d indices (%d triangles)", ImGui::GetIO().MetricsRenderVertices, ImGui::GetIO().MetricsRenderIndices, ImGui::GetIO().MetricsRenderIndices / 3);
			ImGui::End();
		}

		void GraphicsContext::renderLoop()
		{
			while (!_window->isClosed())
			{
				_frametimer.reset();
				_window->update();
				root->getRenderer()->setViewport(0, 0, _window->width(), _window->height());
				root->getRenderer()->clear();

				_guiLoader->newFrame();

				_internalRender();
				onRender();

				ImGui::Render();
				_guiLoader->renderDrawLists(ImGui::GetDrawData());
				_window->present();
				_tpf = _frametimer.elapsedMillis();
				if (_framerateTimer.elapsedMillis() > 100.0f && _isdebuggui)
				{
					_framerateTimer.reset();
					std::rotate(_frameratebuf.begin(), _frameratebuf.begin()+1,_frameratebuf.end());
					_frameratebuf[_frameratebuf.size()-1] = 1000.0f / _tpf;
				}
				if(_isdebuggui) _isdebuggui = false;
			}
		}

		void GraphicsContext::_internalRender()
		{}

		void GraphicsContext::addInputListener(InputListener* in)
		{
			root->inputHandler->addKeyCallback([in](InputKey key, int scancode, InputAction action, InputMod mods) {
				if(action == InputAction::Pressed)
					in->keyPressed({static_cast<int>(key), scancode, static_cast<ushort>(mods)});
				else if(action == InputAction::Released)
					in->keyReleased({static_cast<int>(key), scancode, static_cast<ushort>(mods)});
			});
			root->inputHandler->addMouseButtonCallback([in](InputButton btn, InputAction action, InputMod mods) {
				if(action == InputAction::Pressed)
					in->mousePressed({static_cast<int>(btn), static_cast<ushort>(mods)});
				else if(action == InputAction::Released)
					in->mouseReleased({static_cast<int>(btn), static_cast<ushort>(mods)});
			});
		}
	}
}
