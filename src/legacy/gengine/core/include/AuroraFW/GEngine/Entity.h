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

#ifndef AURORAFW_GENGINE_ENTITY_H
#define AURORAFW_GENGINE_ENTITY_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

namespace AuroraFW::GEngine {
	class AFW_API Entity {
	public:
		Entity();
	
		void addComponent(Component* );

		template <typename T>
		const T* getComponent() const
		{
			return _getComponent<T>();
		}

		template <typename T>
		T* getComponent()
		{
			return (T*)_getComponent<T>();
		}

	protected:
		std::unordered_map<ComponentType*, Component*> _components;

	private:
		template <typename T>
		const T* _getComponent() const
		{
			ComponentType* type = T::getStaticType();
			auto it = _components.find(type);
			if (it == _components.end())
				return AFW_NULLPTR;
			return (T*)it->second;
		}
	};
}

#endif // AURORAFW_GENGINE_ENTITY_H