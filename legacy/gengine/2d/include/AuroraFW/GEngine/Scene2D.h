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

#ifndef AURORAFW_GENGINE_SCENE2D_H
#define AURORAFW_GENGINE_SCENE2D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

namespace AuroraFW::GEngine {
	class AFW_API Scene2D {
	public:
		Scene2D();
		Scene2D(const Math::Matrix4x4& );
		~Scene2D();

		void add(Entity* );

		virtual void onUpdate();
		virtual void onRender(Renderer2D& );

		void onRender();

		AFW_FORCE_INLINE Renderer2D* getRenderer() { return _renderer; }
		AFW_FORCE_INLINE OrthographicCamera* getCamera() { return _camera; }
	private:
		Renderer2D* _renderer;
		OrthographicCamera* _camera;
		std::vector<Entity*> _entities;
	};
}

#endif // AURORAFW_GENGINE_SCENE2D_H