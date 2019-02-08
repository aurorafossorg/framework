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

#ifndef AURORAFW_GENGINE_VULKAN_CONTEXT_H
#define AURORAFW_GENGINE_VULKAN_CONTEXT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/Vulkan/Global.h>

#include <AuroraFW/GEngine/API/Context.h>

#include <memory>

namespace AuroraFW {
	namespace GEngine {
		namespace Vulkan {
			struct AFW_API PhysicalDevice {
				vk::PhysicalDevice device;
				vk::PhysicalDeviceFeatures features;
				vk::PhysicalDeviceProperties properties;
				vk::PhysicalDeviceMemoryProperties memoryProperties;
				bool isPrimary = false;
				uint32_t index;
			};

			/*struct AFW_API QueueFamilyIndices {
				int graphicsFamily = -1;
				int presentFamily = -1;
			};*/
		}
		class AFW_API VKContext : public API::Context
		{
		public:
			VKContext(std::string& );

			inline static VKContext* getInstance() { return (VKContext*)_instance; }

#ifdef AFW__DEBUG
			static const std::vector<const char*> validationLayers;
#endif

		protected:
			void _init(GLFWwindow* ) override;
			void _destroy() override;

		private:
			//Vulkan::QueueFamilyIndices _findQueueFamilies(vk::PhysicalDevice );

			std::string& _name;
			vk::Instance _vkinstance;
			vk::SurfaceKHR _vksurface;
			uint primaryIndex;
			std::vector<std::shared_ptr<Vulkan::PhysicalDevice>> _vkphysicalDevices;

#ifdef AFW__DEBUG
			VkDebugReportCallbackEXT _vkcallback;
#endif
		};
	}
}

#endif // AURORAFW_GENGINE_VULKAN_CONTEXT_H
