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