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

#ifndef AURORAFW_IO_FLAGS_H
#define AURORAFW_IO_FLAGS_H

namespace AuroraFW {
	namespace IO {
		enum Flags {
			Read =   0b001,
			Write =  0b010,
			Append = 0b111
		};

		inline Flags operator|(Flags a, Flags b)
		{
			return static_cast<Flags>(static_cast<int>(a) | static_cast<int>(b));
		}

		inline Flags operator&(Flags a, Flags b)
		{
			return static_cast<Flags>(static_cast<int>(a) & static_cast<int>(b));
		}

		inline Flags operator~(Flags a)
		{
			return static_cast<Flags>(~static_cast<int>(a));
		}
	}
}

#endif // AURORAFW_IO_FLAGS_H