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

#include <AuroraFW/GEngine/Vulkan/Context.h>

#include <AuroraFW/STDL/STL/IOStream.h>
#include <set>

namespace AuroraFW {
	namespace GEngine {
		VKContext::VKContext(std::string &name)
			: _name(name)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}

		void VKContext::_init(GLFWwindow* window)
		{
#ifdef AFW__DEBUG
			uint32_t vk_layerCount;
			vk::enumerateInstanceLayerProperties(&vk_layerCount, AFW_NULLPTR);

			std::vector<vk::LayerProperties> vk_availableLayers(vk_layerCount);
			vk::enumerateInstanceLayerProperties(&vk_layerCount, vk_availableLayers.data());

			for (const char* vk_layerName : VKContext::validationLayers) {
				bool vk_layerFound = false;

				for (const vk::LayerProperties& vk_layerProperties : vk_availableLayers) {
					if (strcmp(vk_layerName, vk_layerProperties.layerName) == 0) {
						vk_layerFound = true;
						break;
					}
				}

				if (!vk_layerFound) {
					throw std::runtime_error("VulkanContext: validation layers requested, but not available!");
				}
			}
#endif // AFW__DEBUG
			vk::ApplicationInfo vk_appInfo(_name.c_str(), 0, "Aurora Framework", VK_MAKE_VERSION(AURORAFW_VERSION_MAJOR, AURORAFW_VERSION_MINOR, AURORAFW_VERSION_REVISION), VK_API_VERSION_1_0);

			vk::InstanceCreateInfo vk_createInfo(vk::InstanceCreateFlags(), &vk_appInfo);

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef AFW__DEBUG
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif // AFW__DEBUG

			vk_createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			vk_createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef AFW__DEBUG
			vk_createInfo.enabledLayerCount = static_cast<uint32_t>(VKContext::validationLayers.size());
			vk_createInfo.ppEnabledLayerNames = VKContext::validationLayers.data();
#else
			vk_createInfo.enabledLayerCount = 0;
#endif // AFW__DEBUG

			if(vk::createInstance(&vk_createInfo, AFW_NULLPTR, &_vkinstance) !=vk::Result::eSuccess)
				throw std::runtime_error("VulkanContext: failed to create Vulkan instance!");

#ifdef AFW__DEBUG
			VkDebugReportCallbackCreateInfoEXT vk_debug_createinfo = {};
			vk_debug_createinfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			vk_debug_createinfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
			vk_debug_createinfo.pfnCallback = [](VkDebugReportFlagsEXT , VkDebugReportObjectTypeEXT , uint64_t , size_t , int32_t , const char* , const char* msg, void* )->VkBool32 {
				std::cerr << "validation layer: " << msg << std::endl;
				return VK_FALSE;
			};
			PFN_vkCreateDebugReportCallbackEXT func = (PFN_vkCreateDebugReportCallbackEXT) _vkinstance.getProcAddr("vkCreateDebugReportCallbackEXT");
			VkResult vk_ret;
			if (func != AFW_NULLPTR) {
				vk_ret = func(_vkinstance, &vk_debug_createinfo, AFW_NULLPTR, &_vkcallback);
			} else {
				vk_ret = VK_ERROR_EXTENSION_NOT_PRESENT;
			}
			if(vk_ret != VK_SUCCESS)
				throw std::runtime_error("failed to set up debug callback!");
#endif // AFW__DEBUG
			VkSurfaceKHR vk_surface;
			if (glfwCreateWindowSurface(_vkinstance, window, AFW_NULLPTR, &vk_surface) != VK_SUCCESS)
				throw std::runtime_error("VulkanContext: failed to create window surface!");
			_vksurface = vk_surface;

			uint32_t vk_deviceCount = AFW_NULLVAL;
			_vkinstance.enumeratePhysicalDevices(&vk_deviceCount, AFW_NULLPTR);

			if(vk_deviceCount == AFW_NULLVAL)
				throw std::runtime_error("VulkanContext: failed to find GPUs with Vulkan support!");

			std::vector<vk::PhysicalDevice> vk_physicalDevices(vk_deviceCount);
			_vkinstance.enumeratePhysicalDevices(&vk_deviceCount, vk_physicalDevices.data());

			_vkphysicalDevices = std::vector<std::shared_ptr<Vulkan::PhysicalDevice>>(vk_deviceCount);
			int i = 0;
			for (const vk::PhysicalDevice &vk_physicalDevice : vk_physicalDevices)
			{
				_vkphysicalDevices[i] = std::shared_ptr<Vulkan::PhysicalDevice>(AFW_NEW Vulkan::PhysicalDevice);
				_vkphysicalDevices[i]->device = vk_physicalDevice;
				vk_physicalDevice.getFeatures(&_vkphysicalDevices[i]->features);
				vk_physicalDevice.getProperties(&_vkphysicalDevices[i]->properties);
				vk_physicalDevice.getMemoryProperties(&_vkphysicalDevices[i]->memoryProperties);
				i++;
			}

			/*
			Vulkan::QueueFamilyIndices vk_indices;
			for(const vk::PhysicalDevice& vk_pdevice : vk_devices)
			{
				Vulkan::QueueFamilyIndices vk_indicesi = _findQueueFamilies(vk_pdevice);

				if(vk_indicesi.graphicsFamily >= 0 && vk_indicesi.presentFamily >= 0)
				{
					vk_indices = vk_indicesi;
					_vkphysicalDevice = vk_pdevice;
					break;
				}
			}

			if (!_vkphysicalDevice)
				throw std::runtime_error("failed to find a suitable GPU!");

			std::vector<vk::DeviceQueueCreateInfo> vk_queueCreateInfos;
			std::set<int> vk_uniqueQueueFamilies = {vk_indices.graphicsFamily, vk_indices.presentFamily};

			float vk_queuePriority = 1.0f;
			for (int vk_queueFamily : vk_uniqueQueueFamilies) {
				vk::DeviceQueueCreateInfo queueCreateInfo(vk::DeviceQueueCreateFlags(), vk_queueFamily, 1, &vk_queuePriority);
				vk_queueCreateInfos.push_back(queueCreateInfo);
			}

			vk::PhysicalDeviceFeatures deviceFeatures = {};

			vk::DeviceCreateInfo vk_device_createInfo(vk::DeviceCreateFlags(), static_cast<uint32_t>(vk_queueCreateInfos.size()), vk_queueCreateInfos.data());

			vk_device_createInfo.pEnabledFeatures = &deviceFeatures;
			vk_device_createInfo.enabledExtensionCount = 0;

#ifdef AFW__DEBUG
				vk_device_createInfo.enabledLayerCount = static_cast<uint32_t>(VKContext::validationLayers.size());
				vk_device_createInfo.ppEnabledLayerNames = VKContext::validationLayers.data();
#else
				vk_device_createInfo.enabledLayerCount = 0;
#endif

			if (_vkphysicalDevice.createDevice(&vk_device_createInfo, AFW_NULLPTR, &_vkdevice) != vk::Result::eSuccess)
				throw std::runtime_error("failed to create logical device!");

			_vkdevice.getQueue(vk_indices.graphicsFamily, 0, &_vkgraphicsQueue);
			_vkdevice.getQueue(vk_indices.presentFamily, 0, &_vkpresentQueue);
			*/
		}

		void VKContext::_destroy()
		{
#ifdef AFW__DEBUG
			PFN_vkDestroyDebugReportCallbackEXT func = (PFN_vkDestroyDebugReportCallbackEXT) _vkinstance.getProcAddr("vkDestroyDebugReportCallbackEXT");
			if (func != AFW_NULLPTR)
				func(_vkinstance, _vkcallback, AFW_NULLPTR);
#endif // AFW__DEBUG
			_vkinstance.destroy();
		}

#ifdef AFW__DEBUG
		const std::vector<const char*> VKContext::validationLayers = {
				"VK_LAYER_LUNARG_standard_validation"
		};
#endif // AFW__DEBUG

		/*
		Vulkan::QueueFamilyIndices VKContext::_findQueueFamilies(vk::PhysicalDevice device) {
			uint32_t vk_queueFamilyCount = 0;
			device.getQueueFamilyProperties(&vk_queueFamilyCount, AFW_NULLPTR);

			std::vector<vk::QueueFamilyProperties> vk_queueFamilies(vk_queueFamilyCount);
			device.getQueueFamilyProperties(&vk_queueFamilyCount, vk_queueFamilies.data());

			int i = 0;
			Vulkan::QueueFamilyIndices vk_indices;
			for (const auto& vk_queueFamily : vk_queueFamilies) {
				if (vk_queueFamily.queueCount > 0 && vk_queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
					vk_indices.graphicsFamily = i;
				}

				VkBool32 vk_presentSupport = false;
				device.getSurfaceSupportKHR(i, _vksurface, &vk_presentSupport);

				if (vk_queueFamily.queueCount > 0 && vk_presentSupport) {
					vk_indices.presentFamily = i;
				}

				if (vk_indices.graphicsFamily >= 0 && vk_indices.presentFamily >= 0) {
					break;
				}

				i++;
			}

			return vk_indices;
		}
		*/
	}
}
