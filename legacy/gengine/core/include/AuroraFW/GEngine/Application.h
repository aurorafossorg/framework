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

/** @file AuroraFW/GEngine/Application.h
 * Application header. Contais the Application
 * class, which is needed to build an application
 * on AuroraFW.
 * @since snapshot20170930
 */

#ifndef AURORAFW_GENGINE_APPLICATION_H
#define AURORAFW_GENGINE_APPLICATION_H

#include <AuroraFW/Global.h>
#include <AuroraFW/_GEngine.h>

#include <AuroraFW/GEngine/API/Context.h>
#include <AuroraFW/Core/Application.h>
#include <iostream>

namespace AuroraFW {
	namespace GEngine {

		/**
		 * A class representing an AuroraFW graphical application.
		 * A class that represents an AuroraFW graphical application. It's associated
		 * with a Window. From here, developers are able to use AuroraFW's Graphics
		 * Engine for their projects.
		 * @since snapshot20170930
		 */
		class AFW_API Application {
			friend class Window;
		public:
			/**
			 * Constructs an Application object.
			 * @param name The name of the window.
			 * @param gapi The desired GraphicsAPI backend.
			 * @see ~Application()
			 * @since snapshot20170930
			 */
			Application(const API::RenderAPI& = API::OpenGL);

			/**
			 * Destructs the object.
			 * @see Application()
			 * @since snapshot20170930
			 */
			~Application();

			/**
			 * The copy constructor was deleted, since Application is not suitable to be copied.
			 * @since snapshot20170930
			 */
			Application(const Application&) = delete;

			/**
			 * The copy assignment was deleted, since Application is not suitable to be copied.
			 * @since snapshot20170930
			 */
			Application& operator= (const Application&) = delete;
		};
	}
}

#endif // AURORAFW_GENGINE_APPLICATION_H
