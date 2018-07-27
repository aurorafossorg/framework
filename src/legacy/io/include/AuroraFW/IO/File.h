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