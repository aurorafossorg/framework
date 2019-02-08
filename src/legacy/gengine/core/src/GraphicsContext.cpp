/*****************************************************************************
**                                     __
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
