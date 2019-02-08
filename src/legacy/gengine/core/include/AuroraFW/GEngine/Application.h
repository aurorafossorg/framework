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
