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

#ifndef AURORAFW_IO_FILE_H
#define AURORAFW_IO_FILE_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/String.h>

#include <AuroraFW/IO/Flags.h>

namespace AuroraFW::IO {
	class FileNotFoundException: public std::exception
	{
	private:
		const std::string _path;
	public:
		FileNotFoundException(const char *);
		virtual const char* what() const throw();
	};

	class FileAllocationFailedException: public std::exception
	{
	private:
		const std::string _path;
	public:
		FileAllocationFailedException(const char *);
		virtual const char* what() const throw();
	};

	class FileIsReadOnlyException: public std::exception
	{
	private:
		const std::string _path;
	public:
		FileIsReadOnlyException(const char *);
		virtual const char* what() const throw();
	};

	class FileIsWriteOnlyException: public std::exception
	{
	private:
		const std::string _path;
	public:
		FileIsWriteOnlyException(const char *);
		virtual const char* what() const throw();
	};

	class AFW_API File {
		public:
			File(const std::string &, Flags = (Read | Write));
			File(const char* , Flags = (Read | Write));
			void readLine();

		private:
			FILE* _file;
			const char* _path;
			uint_t _len;
	};

	std::string readFile(const std::string& );
}

#endif // AURORAFW_IO_FILE_H