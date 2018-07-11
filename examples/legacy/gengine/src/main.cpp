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
** the GNU General Public License version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3 requirements will be
** met: https://www.gnu.org/licenses/gpl-3.0.html.
****************************************************************************/

#include <AuroraFW/Core/ApplicationContext.h>
#include <AuroraFW/Core/InputListener.h>
#include <AuroraFW/Core/DebugManager.h>
#include <AuroraFW/GEngine/GraphicsContext.h>
#include <AuroraFW/GEngine/Renderable2D.h>
#include <AuroraFW/GEngine/Renderer2D.h>
#include <AuroraFW/GEngine/API/Texture.h>
#include <AuroraFW/GEngine/API/RTShader.h>
#include <AuroraFW/GEngine/API/RTShaderPipeline.h>
#include <AuroraFW/Image/BaseColor.h>
#include <AuroraFW/CLI/Output.h>
#include <AuroraFW/IO/File.h>
#include <time.h>

using namespace AuroraFW;
using namespace GEngine;

class MyApplication : public ApplicationContext, InputListener, public GraphicsContext {
public:
	MyApplication(int& argc, char* argv[])
		: ApplicationContext("GEngine Application Test", argc, argv),
	GraphicsContext("GEngine Test", API::OpenGL)
	{
		addInputListener(this);
	}

	void onStart()
	{
		root->getRenderer()->setBlendFunction(API::Renderer::BlendFunction::SourceAlpha, API::Renderer::BlendFunction::OneMinusSourceAlpha);
		root->getRenderer()->setBlend(true);

		std::unique_ptr<API::RTShader> sunshader_vert = std::unique_ptr<API::RTShader>(API::RTShader::Load(Shader::Type::Vertex, "apps/tests/gengine/rsrc/sun/glsl330_core/shader.vert", API::RTShader::Language::GLSL, API::RTShader::LangVersion::GLSL330_CORE));
		std::unique_ptr<API::RTShader> sunshader_frag = std::unique_ptr<API::RTShader>(API::RTShader::Load(Shader::Type::Fragment, "apps/tests/gengine/rsrc/sun/glsl330_core/shader.frag", API::RTShader::Language::GLSL, API::RTShader::LangVersion::GLSL330_CORE));

		_sunpipeline = std::unique_ptr<API::RTShaderPipeline>(API::RTShaderPipeline::Load({sunshader_vert.get(), sunshader_frag.get()}));

		_sunpipeline->bind();

		_sunpipeline->setValue("prMatrix", Math::Matrix4x4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
		_sunpipeline->setValue("mlMatrix", Math::Matrix4x4::translate(Math::Vector3D(4, 3, 0)));

		srand(time(NULL));

		for (float y = -3.0f; y < 9.0f; y += 0.07)
		{
			for (float x = -4.0f; x < 12.0f; x += 0.07)
			{
				_sprites.push_back(AFW_NEW Renderable2D(Math::Vector3D(x, y, 0), Math::Vector2D(0.05f, 0.05f), ColorF(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f)));
			}
		}

		//_textureSprite = AFW_NEW Renderable2D(Math::Vector3D(5, 5, 0), Math::Vector2D(4, 4), ColorF(1.0f, 0.0f, 1.0f, 1.0f), _sunpipeline.get());
		//_textureSprite2 = AFW_NEW Renderable2D(Math::Vector3D(7, 1, 0), Math::Vector2D(2, 3), ColorF(0.2f, 0.0f, 1.0f, 1.0f), _sunpipeline.get());
		
		_sunpipeline->setValue("lightPos", Math::Vector2D(4.0f, 1.5f));
		_sunpipeline->setValue("colour", Math::Vector4D(0.2f, 0.3f, 0.8f, 1.0f));

		//_sampleTexture = std::unique_ptr<API::Texture>(API::Texture::Load("apps/tests/gengine/rsrc/logo.png"));
		//_sampleTexture->bind(0);

		_renderer2d = AFW_NEW Renderer2D(root->getRenderer(), getWindow()->width(), getWindow()->height());

		root->getRenderer()->setClearColor(ColorF(CommonColor::Black));
	}

	void onRender()
	{
		debug_counter++;
		//DebugManager::Log(debug_counter);
		if(DebugManager::getStatus())
			renderDebugGUI();
		double x, y;
		root->inputHandler->getMousePosition(x, y);

		_sunpipeline->setValue("lightPos", Math::Vector2D((float)(x * 16.0f / getWindow()->width()), (float)(9.0f - y * 9.0f / getWindow()->height())));

		_renderer2d->begin();
		for (int i = 0; i < _sprites.size(); i++)
		{
			//DebugManager::Log(_sprites.size(), ": ", i);
			_renderer2d->submit(_sprites[i]);
		}
		_renderer2d->end();
		_renderer2d->present();
	}

	void onClose()
	{
		//delete _textureSprite;
		delete _renderer2d;
	}

	bool keyPressed(const KeyboardEvent& e)
	{
		CLI::Output << e.key << CLI::EndLine;
		return true;
	}

	private:
		std::vector<Renderable2D*> _sprites;
		Renderer2D* _renderer2d;
		std::unique_ptr<API::RTShaderPipeline> _sunpipeline;
		std::unique_ptr<API::Texture> _sampleTexture;
		size_t debug_counter = 0;
};

int main(int argc, char* argv[])
{
	MyApplication app(argc, argv);
	app.start();
	app.renderLoop();
	app.close();
	return 0;
}