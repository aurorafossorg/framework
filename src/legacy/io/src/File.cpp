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

#include <AuroraFW/IO/File.h>
#include <AuroraFW/STDL/LibC/Assert.h>
#include <AuroraFW/STDL/STL/Algorithm.h>
#include <AuroraFW/STDL/LibC/String.h>

namespace AuroraFW {
	namespace IO {
		File::File(const std::string &path, Flags f)
		{
			_path = path.c_str();
			if(f == Read)
				_file = fopen(_path, "rb");
			else if(f == Write)
				_file = fopen(_path, "wb");
			else if((f == Read) | Write)
				_file = fopen(_path, "rb");
			
			if (_file == nullptr)
				assert(_file);
		}

		AFW_API std::string readFile(const std::string& path)
		{
			FILE* file = fopen(path.c_str(), "rb");
			if (file == nullptr)
				assert(file);

			fseek(file, 0, SEEK_END);
			int32_t length = ftell(file);
			assert(length < 100 * 1024 * 1024);
			std::string result(length, 0);
			fseek(file, 0, SEEK_SET);
			fread(&result[0], 1, length, file);
			fclose(file);

			result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
			return result;
		}
	}
}