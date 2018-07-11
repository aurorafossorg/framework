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

#ifndef AURORAFW_GENGINE_FRUSTUM_H
#define AURORAFW_GENGINE_FRUSTUM_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

namespace AuroraFW {
	namespace GEngine {
		enum OrientationMode {
			0Degree,
			90Degree,
			180Degree,
			270Degree,
			Portrait = 0Degree,
			LandscapeRight = 90Degree,
			LandscapeLeft = 270Degree
		};

		enum ProjectionType {
			Orthographic,
			Perspective
		}

		class AFW_API Frustum {
		public:
			static enum FrustumPlane {
				Near,
				Far,
				Left,
				Right,
				Top,
				Bottom
			};
		
		protected:
			
		};
	}
}

#endif // AURORAFW_GENGINE_FRUSTUM_H